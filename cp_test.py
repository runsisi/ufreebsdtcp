#! /usr/bin/env python
# encoding: utf-8
'''
Created on 2013/12/03

@author: runsisi AT hust.edu.cn
'''

from subprocess import Popen, call, PIPE
from os.path import exists, join, abspath
from os import curdir
from re import compile
from datetime import datetime

def main():
    logfile = '/home/lrb/perf_test.log'
    middir = '/home/lrb/testfile'
    nfsdir = '/home/lrb/nfs'
    srcdir = abspath(curdir)
    mountedstr = r'\s/home/lrb/nfs\s'
    datfiles = [('32m.dat', 32), ('64m.dat', 64), ('128m.dat', 128),
             ('256m.dat', 256), ('512m.dat', 512), ('1g.dat', 1024),
             ('2g.dat', 2048), ('3g.dat', 3072), ('4g.dat', 4096),
             ('5g.dat', 5120), ('6g.dat', 6144),]
    # check if mounted
    p = Popen(['mount'], stdout=PIPE, stderr=PIPE)
    (out, err) = p.communicate()
    if p.returncode:
        print('Failed to query mounted fs, abort')
        return 1
    e = compile(mountedstr)
    m = None
    out = out.split('\n')
    for ln in out:
        m = e.search(ln)
        if m:
            break
    if not m:
        print('{0} not mounted, pls mount it first, abort!'.format(nfsdir))
        return 1
    print('1>. Cleaning directories:\n'
          '    {0}, {1}'.format(middir, nfsdir))
    if not exists(middir):
        call(['mkdir', middir])
    else:
        call('rm -rf ' + middir + '/*', shell=True)
    call('rm -rf ' + nfsdir + '/*', shell=True)
    print('\n2>. Open log file to append:\n'
          '    {0}'.format(logfile))
    log = open(logfile, 'a+')
    log.write(str(datetime.now()) + '\n')
    print('\n3>. Copying in test')
    for (fname, size) in datfiles:
        print('copy in: {0}, size: {1}M'.format(fname, size))
        srcfname = join(srcdir, fname)
        dstfname = join(nfsdir, fname)
        p = Popen(['time', '-p', 'cp', srcfname, dstfname], stdout=PIPE, stderr=PIPE)
        (out, err) = p.communicate()
        if p.returncode != 0:
            print('copy in operation failed, code: {0}'.format(p.returncode))
        else:
            # write to log file for later use
            log.write(srcfname + ' --> ' + dstfname + ':\n')
            # get time
            err = err.split('\n')[0]    # get first line
            err = err.split()           # get time
            t = float(err[1])
            if t == 0:
                speed = 'inf'
            else:
                speed = str(size / t)
            log.write('size: {0}M, time: {1}s, speed: {2}M/s\n\n'.format(size, t, speed))
    print('\n4>. Copying out test')
    for (fname, size) in datfiles:
        print('copy out: {0}, size: {1}M'.format(fname, size))
        srcfname = join(nfsdir, fname)
        dstfname = join(middir, fname)
        p = Popen(['time', '-p', 'cp', srcfname, dstfname], stdout=PIPE, stderr=PIPE)
        (out, err) = p.communicate()
        if p.returncode != 0:
            print('copy out operation failed, code: {0}'.format(p.returncode))
        else:
            # write to log file for later use
            log.write(srcfname + ' --> ' + dstfname + ':\n')
            # get time
            err = err.split('\n')[0]    # get first line
            err = err.split()           # get time
            t = float(err[1])
            if t == 0:
                speed = 'inf'
            else:
                speed = str(size / t)
            log.write('size: {0}M, time: {1}s, speed: {2}M/s\n\n'.format(size, t, speed))
    # close log file
    log.write('\n\n')
    log.close()
    print('\n5>. OK, everything went ok:)\n'
          '    Refer to {0} to see the results!'.format(logfile))
    return 0

if __name__ == '__main__':
    main()
