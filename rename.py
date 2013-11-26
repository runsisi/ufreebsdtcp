#! /usr/bin/env python
# encoding: utf-8
'''
Created on 2013/10/16

@author: runsisi AT hust.edu.cn
'''
from re import compile, DOTALL
from os import walk, rename, curdir
from os.path import join, basename

def rename_headers(rdir):    
    s = r'^(_*)([\w-]+\.h)$'
    e = compile(s)
    for (pdir, dirs, fns) in walk(rdir):        
        for fn in fns:           
            m = e.match(fn)
            if m:
                ofn = join(pdir, fn)
                nfn = join(pdir, m.group(1) + 'bsd_' + m.group(2))
                print('{0} => {1}'.format(fn, basename(nfn)))
                rename(ofn, nfn)

def rename_includes(rdir):
    #s = r'^(\s*#include\s*<\s*[\w/]*?/?_*)(\w+\.h\s*>.*)$'
    s = r'^(\s*#include\s*<\s*(?:sys|machine|x86)/[\w/-]*?_*)([\w-]+\.h\s*>.*)$'    
    e = compile(s, DOTALL)    
    for (pdir, dirs, fns) in walk(rdir):
        if basename(__file__) in fns:
            fns.remove(basename(__file__))
        for fn in fns: 
            if fn[-2:] not in ['.h', '.c']:
                continue
            with open(join(pdir, fn), 'r') as f:
                lns = f.readlines()
            with open(join(pdir, fn), 'w') as f:
                for ln in lns:
                    m = e.match(ln)
                    if m:
                        ln = m.group(1) + 'bsd_' + m.group(2)   
                    f.write(ln)
                    
def comment_includes(rdir):    
    s = r'^(\s*#include\s*<\s*(?:security|ddb|fs)/.*)$'    
    e = compile(s, DOTALL)
    for (pdir, dirs, fns) in walk(rdir):
        if basename(__file__) in fns:
            fns.remove(basename(__file__))
        for fn in fns: 
            if fn[-2:] not in ['.h', '.c']:
                continue
            with open(join(pdir, fn), 'r') as f:
                lns = f.readlines()
            with open(join(pdir, fn), 'w') as f:
                for ln in lns:
                    m = e.match(ln)
                    if m:
                        ln = '//' + m.group(1)  
                    f.write(ln)

if __name__ == '__main__':
    c = raw_input('Now is your choice (input the digit 1 or 2 or 3 then press enter): \n'
              '1) Add a bsd_ prefix to all the header file names\n'
              '2) Add a bsd_ prefix for all the #include directives in .h/.c files\n'
              '3) Comment out security and ddb and fs includes\n\n'
              'N.B.: This script will only affect the files under current directory:)\n')
    if c in ['1', '2', '3']:
        if c == '1':
            rename_headers(curdir)        
        elif c == '2':
            rename_includes(curdir)
        else:
            comment_includes(curdir)
        print('Done!')
    else:
        print('As you wish, nothing has been done :)')
    raw_input('\nPress enter to exit!')