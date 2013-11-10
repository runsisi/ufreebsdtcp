#ifndef _FEEDER_EQ_GEN_H_
#define _FEEDER_EQ_GEN_H_

/*
 * Generated using feeder_eq_mkfilter.awk, heaven, wind and awesome.
 *
 * DO NOT EDIT!
 */

/*
 * EQ: Peaking EQ
 */
#define FEEDER_EQ_PRESETS	"PEQ:16000,0.2500,62,0.2500:-9,9,1.0:44100,48000,88200,96000,176400,192000"

struct feed_eq_coeff_tone {
	int32_t a1, a2;
	int32_t b0, b1, b2;
};

struct feed_eq_coeff {
	struct feed_eq_coeff_tone treble;
	struct feed_eq_coeff_tone bass;
};

static struct feed_eq_coeff eq_44100[19] = {
     {{  0x005de957, -0x006fba89,  0x00895f8a,  0x005de957,  0x0006e5ed },
      { -0x01f13b8a,  0x00f14082,  0x00fb3e0d, -0x01f13b8a,  0x00f60274 }},
     {{  0x0061d7ab, -0x0069b090,  0x0093269a,  0x0061d7ab,  0x000328d6 },
      { -0x01f208fa,  0x00f20df4,  0x00fbcd9b, -0x01f208fa,  0x00f64058 }},
     {{  0x0065de32, -0x0063816b,  0x009da57f,  0x0065de32, -0x000126eb },
      { -0x01f2cb88,  0x00f2d083,  0x00fc5a25, -0x01f2cb88,  0x00f6765f }},
     {{  0x0069fc09, -0x005d2e76,  0x00a8e973,  0x0069fc09, -0x000617e9 },
      { -0x01f383c0,  0x00f388bd,  0x00fce414, -0x01f383c0,  0x00f6a4a9 }},
     {{  0x006e302f, -0x0056b93b,  0x00b50085,  0x006e302f, -0x000bb9c0 },
      { -0x01f43226,  0x00f43725,  0x00fd6bd3, -0x01f43226,  0x00f6cb52 }},
     {{  0x00727984, -0x00502374,  0x00c1f9ac,  0x00727984, -0x00121d20 },
      { -0x01f4d73b,  0x00f4dc3c,  0x00fdf1ca, -0x01f4d73b,  0x00f6ea72 }},
     {{  0x0076d6cd, -0x00496f07,  0x00cfe4cd,  0x0076d6cd, -0x001953d4 },
      { -0x01f57378,  0x00f5787b,  0x00fe7661, -0x01f57378,  0x00f70219 }},
     {{  0x007b46ae, -0x00429e09,  0x00ded2c8,  0x007b46ae, -0x002170d1 },
      { -0x01f60752,  0x00f60c55,  0x00fefa02, -0x01f60752,  0x00f71253 }},
     {{  0x007fc7b3, -0x003bb2b6,  0x00eed585,  0x007fc7b3, -0x002a883b },
      { -0x01f69336,  0x00f6983b,  0x00ff7d14, -0x01f69336,  0x00f71b27 }},
     {{  0x0084584c, -0x0034af74,  0x01000000,  0x0084584c, -0x0034af74 },
      { -0x01f7178e,  0x00f71c94,  0x01000000, -0x01f7178e,  0x00f71c94 }},
     {{  0x0088f6d1, -0x002d96cf,  0x01126654,  0x0088f6d1, -0x003ffd23 },
      { -0x01f794bf,  0x00f799c7,  0x0100832f, -0x01f794bf,  0x00f71698 }},
     {{  0x008da185, -0x00266b74,  0x01261dcb,  0x008da185, -0x004c893f },
      { -0x01f80b29,  0x00f81032,  0x0101070b, -0x01f80b29,  0x00f70927 }},
     {{  0x00925695, -0x001f302c,  0x013b3cea,  0x00925695, -0x005a6d17 },
      { -0x01f87b26,  0x00f88030,  0x01018bff, -0x01f87b26,  0x00f6f430 }},
     {{  0x00971420, -0x0017e7df,  0x0151db84,  0x00971420, -0x0069c363 },
      { -0x01f8e50d,  0x00f8ea18,  0x01021279, -0x01f8e50d,  0x00f6d79f }},
     {{  0x009bd835, -0x00109585,  0x016a12c3,  0x009bd835, -0x007aa848 },
      { -0x01f94930,  0x00f94e3c,  0x01029ae5, -0x01f94930,  0x00f6b357 }},
     {{  0x00a0a0d9, -0x00093c2c,  0x0183fd3e,  0x00a0a0d9, -0x008d3969 },
      { -0x01f9a7de,  0x00f9aceb,  0x010325b5, -0x01f9a7de,  0x00f68736 }},
     {{  0x00a56c08, -0x0001dee9,  0x019fb708,  0x00a56c08, -0x00a195f2 },
      { -0x01fa0160,  0x00fa066e,  0x0103b35b, -0x01fa0160,  0x00f65313 }},
     {{  0x00aa37bc,  0x00057f24,  0x01bd5dc6,  0x00aa37bc, -0x00b7dea2 },
      { -0x01fa55fe,  0x00fa5b0d,  0x0104444d, -0x01fa55fe,  0x00f616c0 }},
     {{  0x00af01eb,  0x000cdade,  0x01dd10bf,  0x00af01eb, -0x00d035e1 },
      { -0x01faa5fa,  0x00faab09,  0x0104d903, -0x01faa5fa,  0x00f5d206 }}
};

static struct feed_eq_coeff eq_48000[19] = {
     {{  0x004182ac, -0x007cfaa7,  0x00851944,  0x004182ac, -0x000213eb },
      { -0x01f266eb,  0x00f26b1f,  0x00fb9e62, -0x01f266eb,  0x00f6ccbd }},
     {{  0x00445b0f, -0x007749e1,  0x008f0ee9,  0x00445b0f, -0x000658ca },
      { -0x01f32487,  0x00f328bd,  0x00fc22b6, -0x01f32487,  0x00f70607 }},
     {{  0x0047473e, -0x00717183,  0x0099ca5b,  0x0047473e, -0x000b3bde },
      { -0x01f3d80d,  0x00f3dc43,  0x00fca438, -0x01f3d80d,  0x00f7380b }},
     {{  0x004a46c1, -0x006b727e,  0x00a55a9c,  0x004a46c1, -0x0010cd1a },
      { -0x01f481fe,  0x00f48636,  0x00fd234c, -0x01f481fe,  0x00f762ea }},
     {{  0x004d5908, -0x00654df1,  0x00b1cfb2,  0x004d5908, -0x00171da2 },
      { -0x01f522d7,  0x00f52711,  0x00fda053, -0x01f522d7,  0x00f786be }},
     {{  0x00507d6b, -0x005f052a,  0x00bf3ab3,  0x00507d6b, -0x001e3fdd },
      { -0x01f5bb11,  0x00f5bf4c,  0x00fe1bb0, -0x01f5bb11,  0x00f7a39c }},
     {{  0x0053b32c, -0x005899a7,  0x00cdadd5,  0x0053b32c, -0x0026477c },
      { -0x01f64b1b,  0x00f64f57,  0x00fe95c2, -0x01f64b1b,  0x00f7b995 }},
     {{  0x0056f976, -0x00520d14,  0x00dd3c79,  0x0056f976, -0x002f498d },
      { -0x01f6d362,  0x00f6d7a0,  0x00ff0eea, -0x01f6d362,  0x00f7c8b6 }},
     {{  0x005a4f5b, -0x004b614b,  0x00edfb3b,  0x005a4f5b, -0x00395c85 },
      { -0x01f7544e,  0x00f7588d,  0x00ff8789, -0x01f7544e,  0x00f7d103 }},
     {{  0x005db3d7, -0x00449851,  0x01000000,  0x005db3d7, -0x00449851 },
      { -0x01f7ce41,  0x00f7d280,  0x01000000, -0x01f7ce41,  0x00f7d280 }},
     {{  0x006125d3, -0x003db45a,  0x01136206,  0x006125d3, -0x00511660 },
      { -0x01f84197,  0x00f845d7,  0x010078b0, -0x01f84197,  0x00f7cd28 }},
     {{  0x0064a420, -0x0036b7bf,  0x012839f3,  0x0064a420, -0x005ef1b2 },
      { -0x01f8aeaa,  0x00f8b2ec,  0x0100f1fa, -0x01f8aeaa,  0x00f7c0f2 }},
     {{  0x00682d7f, -0x002fa501,  0x013ea1e4,  0x00682d7f, -0x006e46e5 },
      { -0x01f915cf,  0x00f91a11,  0x01016c42, -0x01f915cf,  0x00f7adcf }},
     {{  0x006bc09e, -0x00287ec4,  0x0156b581,  0x006bc09e, -0x007f3445 },
      { -0x01f97755,  0x00f97b98,  0x0101e7eb, -0x01f97755,  0x00f793ac }},
     {{  0x006f5c1b, -0x002147c9,  0x0170920c,  0x006f5c1b, -0x0091d9d5 },
      { -0x01f9d389,  0x00f9d7cd,  0x0102655d, -0x01f9d389,  0x00f77270 }},
     {{  0x0072fe88, -0x001a02f0,  0x018c5673,  0x0072fe88, -0x00a65964 },
      { -0x01fa2ab4,  0x00fa2ef8,  0x0102e4fd, -0x01fa2ab4,  0x00f749fb }},
     {{  0x0076a669, -0x0012b32e,  0x01aa2367,  0x0076a669, -0x00bcd695 },
      { -0x01fa7d1a,  0x00fa815f,  0x01036736, -0x01fa7d1a,  0x00f71a29 }},
     {{  0x007a523c, -0x000b5b88,  0x01ca1b6c,  0x007a523c, -0x00d576f5 },
      { -0x01facafc,  0x00facf42,  0x0103ec74, -0x01facafc,  0x00f6e2ce }},
     {{  0x007e0076, -0x0003ff15,  0x01ec62f3,  0x007e0076, -0x00f06208 },
      { -0x01fb149a,  0x00fb18e0,  0x01047526, -0x01fb149a,  0x00f6a3ba }}
};

static struct feed_eq_coeff eq_88200[19] = {
     {{ -0x0034ce99, -0x0081990d,  0x00839bd5, -0x0034ce99, -0x000534e2 },
      { -0x01f88364,  0x00f884a6,  0x00fd961f, -0x01f88364,  0x00faee87 }},
     {{ -0x0037212c, -0x007c09d9,  0x008da0f8, -0x0037212c, -0x0009aad1 },
      { -0x01f8ed0d,  0x00f8ee50,  0x00fddf62, -0x01f8ed0d,  0x00fb0eef }},
     {{ -0x0039848e, -0x00765265,  0x009870d7, -0x0039848e, -0x000ec33d },
      { -0x01f950f7,  0x00f9523a,  0x00fe26fa, -0x01f950f7,  0x00fb2b40 }},
     {{ -0x003bf86c, -0x0070737e,  0x00a41b1e, -0x003bf86c, -0x00148e9d },
      { -0x01f9af6d,  0x00f9b0b0,  0x00fe6d22, -0x01f9af6d,  0x00fb438f }},
     {{ -0x003e7c5e, -0x006a6e1d,  0x00b0b08d, -0x003e7c5e, -0x001b1eaa },
      { -0x01fa08bc,  0x00fa09ff,  0x00feb211, -0x01fa08bc,  0x00fb57ee }},
     {{ -0x00410fe7, -0x00644369,  0x00be4307, -0x00410fe7, -0x0022866f },
      { -0x01fa5d28,  0x00fa5e6c,  0x00fef5ff, -0x01fa5d28,  0x00fb686c }},
     {{ -0x0043b279, -0x005df4b7,  0x00cce59e, -0x0043b279, -0x002ada56 },
      { -0x01faacf5,  0x00faae39,  0x00ff3925, -0x01faacf5,  0x00fb7514 }},
     {{ -0x00466371, -0x0057838e,  0x00dcaca9, -0x00466371, -0x00343036 },
      { -0x01faf863,  0x00faf9a7,  0x00ff7bb8, -0x01faf863,  0x00fb7def }},
     {{ -0x0049221a, -0x0050f1a0,  0x00edadc8, -0x0049221a, -0x003e9f69 },
      { -0x01fb3fad,  0x00fb40f1,  0x00ffbdef, -0x01fb3fad,  0x00fb8303 }},
     {{ -0x004bedaa, -0x004a40d0,  0x01000000, -0x004bedaa, -0x004a40d0 },
      { -0x01fb830d,  0x00fb8451,  0x01000000, -0x01fb830d,  0x00fb8451 }},
     {{ -0x004ec545, -0x0043732b,  0x0113bbc2, -0x004ec545, -0x00572eed },
      { -0x01fbc2b8,  0x00fbc3fc,  0x01004223, -0x01fbc2b8,  0x00fb81da }},
     {{ -0x0051a7fe, -0x003c8aea,  0x0128fb00, -0x0051a7fe, -0x006585ea },
      { -0x01fbfee2,  0x00fc0027,  0x0100848d, -0x01fbfee2,  0x00fb7b9a }},
     {{ -0x005494d7, -0x00358a6e,  0x013fd93d, -0x005494d7, -0x007563ab },
      { -0x01fc37bc,  0x00fc3901,  0x0100c776, -0x01fc37bc,  0x00fb718a }},
     {{ -0x00578ac1, -0x002e743d,  0x015873a0, -0x00578ac1, -0x0086e7de },
      { -0x01fc6d73,  0x00fc6eb8,  0x01010b16, -0x01fc6d73,  0x00fb63a2 }},
     {{ -0x005a88a0, -0x00274b01,  0x0172e905, -0x005a88a0, -0x009a3406 },
      { -0x01fca033,  0x00fca178,  0x01014fa5, -0x01fca033,  0x00fb51d3 }},
     {{ -0x005d8d4a, -0x00201182,  0x018f5a10, -0x005d8d4a, -0x00af6b91 },
      { -0x01fcd026,  0x00fcd16b,  0x0101955c, -0x01fcd026,  0x00fb3c0f }},
     {{ -0x0060978b, -0x0018caa0,  0x01ade944, -0x0060978b, -0x00c6b3e4 },
      { -0x01fcfd73,  0x00fcfeb8,  0x0101dc76, -0x01fcfd73,  0x00fb2242 }},
     {{ -0x0063a626, -0x00117955,  0x01cebb15, -0x0063a626, -0x00e0346a },
      { -0x01fd283e,  0x00fd2983,  0x0102252f, -0x01fd283e,  0x00fb0455 }},
     {{ -0x0066b7d6, -0x000a20ab,  0x01f1f601, -0x0066b7d6, -0x00fc16ac },
      { -0x01fd50ab,  0x00fd51f1,  0x01026fc3, -0x01fd50ab,  0x00fae22e }}
};

static struct feed_eq_coeff eq_96000[19] = {
     {{ -0x004182ac, -0x007cfaa7,  0x00851944, -0x004182ac, -0x000213eb },
      { -0x01f91d1d,  0x00f91e2e,  0x00fdc7a6, -0x01f91d1d,  0x00fb5688 }},
     {{ -0x00445b0f, -0x007749e1,  0x008f0ee9, -0x00445b0f, -0x000658ca },
      { -0x01f97e6b,  0x00f97f7b,  0x00fe0b12, -0x01f97e6b,  0x00fb746a }},
     {{ -0x0047473e, -0x00717183,  0x0099ca5b, -0x0047473e, -0x000b3bde },
      { -0x01f9da69,  0x00f9db7a,  0x00fe4cf3, -0x01f9da69,  0x00fb8e87 }},
     {{ -0x004a46c1, -0x006b727e,  0x00a55a9c, -0x004a46c1, -0x0010cd1a },
      { -0x01fa3161,  0x00fa3272,  0x00fe8d7e, -0x01fa3161,  0x00fba4f4 }},
     {{ -0x004d5908, -0x00654df1,  0x00b1cfb2, -0x004d5908, -0x00171da2 },
      { -0x01fa8397,  0x00fa84a8,  0x00fecce8, -0x01fa8397,  0x00fbb7c0 }},
     {{ -0x00507d6b, -0x005f052a,  0x00bf3ab3, -0x00507d6b, -0x001e3fdd },
      { -0x01fad14c,  0x00fad25d,  0x00ff0b64, -0x01fad14c,  0x00fbc6f9 }},
     {{ -0x0053b32c, -0x005899a7,  0x00cdadd5, -0x0053b32c, -0x0026477c },
      { -0x01fb1abe,  0x00fb1bcf,  0x00ff4925, -0x01fb1abe,  0x00fbd2aa }},
     {{ -0x0056f976, -0x00520d14,  0x00dd3c79, -0x0056f976, -0x002f498d },
      { -0x01fb6028,  0x00fb613a,  0x00ff865e, -0x01fb6028,  0x00fbdadb }},
     {{ -0x005a4f5b, -0x004b614b,  0x00edfb3b, -0x005a4f5b, -0x00395c85 },
      { -0x01fba1c1,  0x00fba2d3,  0x00ffc341, -0x01fba1c1,  0x00fbdf92 }},
     {{ -0x005db3d7, -0x00449851,  0x01000000, -0x005db3d7, -0x00449851 },
      { -0x01fbdfbf,  0x00fbe0d1,  0x01000000, -0x01fbdfbf,  0x00fbe0d1 }},
     {{ -0x006125d3, -0x003db45a,  0x01136206, -0x006125d3, -0x00511660 },
      { -0x01fc1a52,  0x00fc1b64,  0x01003ccd, -0x01fc1a52,  0x00fbde97 }},
     {{ -0x0064a420, -0x0036b7bf,  0x012839f3, -0x0064a420, -0x005ef1b2 },
      { -0x01fc51ab,  0x00fc52be,  0x010079dc, -0x01fc51ab,  0x00fbd8e2 }},
     {{ -0x00682d7f, -0x002fa501,  0x013ea1e4, -0x00682d7f, -0x006e46e5 },
      { -0x01fc85f7,  0x00fc870a,  0x0100b75e, -0x01fc85f7,  0x00fbcfac }},
     {{ -0x006bc09e, -0x00287ec4,  0x0156b581, -0x006bc09e, -0x007f3445 },
      { -0x01fcb760,  0x00fcb872,  0x0100f586, -0x01fcb760,  0x00fbc2ec }},
     {{ -0x006f5c1b, -0x002147c9,  0x0170920c, -0x006f5c1b, -0x0091d9d5 },
      { -0x01fce60e,  0x00fce720,  0x0101348a, -0x01fce60e,  0x00fbb296 }},
     {{ -0x0072fe88, -0x001a02f0,  0x018c5673, -0x0072fe88, -0x00a65964 },
      { -0x01fd1227,  0x00fd133a,  0x0101749d, -0x01fd1227,  0x00fb9e9d }},
     {{ -0x0076a669, -0x0012b32e,  0x01aa2367, -0x0076a669, -0x00bcd695 },
      { -0x01fd3bd0,  0x00fd3ce3,  0x0101b5f5, -0x01fd3bd0,  0x00fb86ed }},
     {{ -0x007a523c, -0x000b5b88,  0x01ca1b6c, -0x007a523c, -0x00d576f5 },
      { -0x01fd632a,  0x00fd643d,  0x0101f8ca, -0x01fd632a,  0x00fb6b73 }},
     {{ -0x007e0076, -0x0003ff15,  0x01ec62f3, -0x007e0076, -0x00f06208 },
      { -0x01fd8857,  0x00fd896a,  0x01023d53, -0x01fd8857,  0x00fb4c17 }}
};

static struct feed_eq_coeff eq_176400[19] = {
     {{ -0x0099526b, -0x0049e5b4,  0x009593cd, -0x0099526b,  0x0020867f },
      { -0x01fc3af5,  0x00fc3b46,  0x00fec8c9, -0x01fc3af5,  0x00fd727d }},
     {{ -0x009f0e08, -0x00431699,  0x009ec48b, -0x009f0e08,  0x001e24dc },
      { -0x01fc708c,  0x00fc70dd,  0x00feedcc, -0x01fc708c,  0x00fd8311 }},
     {{ -0x00a4dff2, -0x003c2d02,  0x00a88702, -0x00a4dff2,  0x001b4bfd },
      { -0x01fca32e,  0x00fca37f,  0x00ff11ef, -0x01fca32e,  0x00fd9190 }},
     {{ -0x00aac626, -0x00352b50,  0x00b2e428, -0x00aac626,  0x0017f088 },
      { -0x01fcd304,  0x00fcd356,  0x00ff3551, -0x01fcd304,  0x00fd9e05 }},
     {{ -0x00b0be84, -0x002e140d,  0x00bde57a, -0x00b0be84,  0x00140678 },
      { -0x01fd0036,  0x00fd0087,  0x00ff580e, -0x01fd0036,  0x00fda879 }},
     {{ -0x00b6c6cb, -0x0026e9e4,  0x00c99507, -0x00b6c6cb,  0x000f8115 },
      { -0x01fd2ae8,  0x00fd2b39,  0x00ff7a43, -0x01fd2ae8,  0x00fdb0f6 }},
     {{ -0x00bcdca4, -0x001faf9d,  0x00d5fd74, -0x00bcdca4,  0x000a52f0 },
      { -0x01fd533d,  0x00fd538e,  0x00ff9c0d, -0x01fd533d,  0x00fdb781 }},
     {{ -0x00c2fda0, -0x0018681b,  0x00e32a05, -0x00c2fda0,  0x00046de0 },
      { -0x01fd7956,  0x00fd79a7,  0x00ffbd88, -0x01fd7956,  0x00fdbc1f }},
     {{ -0x00c9273d, -0x0011165a,  0x00f126a8, -0x00c9273d, -0x00023d02 },
      { -0x01fd9d53,  0x00fd9da4,  0x00ffded0, -0x01fd9d53,  0x00fdbed4 }},
     {{ -0x00cf56ed, -0x0009bd62,  0x01000000, -0x00cf56ed, -0x0009bd62 },
      { -0x01fdbf51,  0x00fdbfa2,  0x01000000, -0x01fdbf51,  0x00fdbfa2 }},
     {{ -0x00d58a16, -0x0002604b,  0x010fc369, -0x00d58a16, -0x001223b4 },
      { -0x01fddf6c,  0x00fddfbe,  0x01002134, -0x01fddf6c,  0x00fdbe89 }},
     {{ -0x00dbbe17,  0x0004fdcf,  0x01207f0a, -0x00dbbe17, -0x001b813c },
      { -0x01fdfdc0,  0x00fdfe11,  0x01004289, -0x01fdfdc0,  0x00fdbb88 }},
     {{ -0x00e1f051,  0x000c59ca,  0x013241da, -0x00e1f051, -0x0025e810 },
      { -0x01fe1a64,  0x00fe1ab6,  0x0100641a, -0x01fe1a64,  0x00fdb69c }},
     {{ -0x00e81e25,  0x0013b08d,  0x01451bb0, -0x00e81e25, -0x00316b24 },
      { -0x01fe3571,  0x00fe35c3,  0x01008603, -0x01fe3571,  0x00fdafc0 }},
     {{ -0x00ee44fc,  0x001aff03,  0x01591d50, -0x00ee44fc, -0x003e1e4c },
      { -0x01fe4efe,  0x00fe4f4f,  0x0100a860, -0x01fe4efe,  0x00fda6ef }},
     {{ -0x00f4624c,  0x00224228,  0x016e5874, -0x00f4624c, -0x004c164c },
      { -0x01fe671f,  0x00fe6770,  0x0100cb50, -0x01fe671f,  0x00fd9c20 }},
     {{ -0x00fa739a,  0x0029770a,  0x0184dfe1, -0x00fa739a, -0x005b68d7 },
      { -0x01fe7de8,  0x00fe7e3a,  0x0100eeef, -0x01fe7de8,  0x00fd8f4b }},
     {{ -0x0100767f,  0x00309ace,  0x019cc771, -0x0100767f, -0x006c2ca3 },
      { -0x01fe936d,  0x00fe93bf,  0x0101135b, -0x01fe936d,  0x00fd8064 }},
     {{ -0x010668aa,  0x0037aab5,  0x01b62426, -0x010668aa, -0x007e7971 },
      { -0x01fea7c0,  0x00fea812,  0x010138b3, -0x01fea7c0,  0x00fd6f5f }}
};

static struct feed_eq_coeff eq_192000[19] = {
     {{ -0x00a58604, -0x0040deb4,  0x00987d50, -0x00a58604,  0x0026a3fc },
      { -0x01fc88dc,  0x00fc8921,  0x00fee1e7, -0x01fc88dc,  0x00fda73a }},
     {{ -0x00ab897d, -0x0039ed12,  0x00a1866c, -0x00ab897d,  0x00248c83 },
      { -0x01fcba27,  0x00fcba6c,  0x00ff03ef, -0x01fcba27,  0x00fdb67d }},
     {{ -0x00b1a125, -0x0032e423,  0x00ab1896, -0x00b1a125,  0x00220347 },
      { -0x01fce8b9,  0x00fce8fe,  0x00ff2529, -0x01fce8b9,  0x00fdc3d5 }},
     {{ -0x00b7cabe, -0x002bc67c,  0x00b53bef, -0x00b7cabe,  0x001efd95 },
      { -0x01fd14b8,  0x00fd14fd,  0x00ff45b1, -0x01fd14b8,  0x00fdcf4c }},
     {{ -0x00be03f1, -0x002496d0,  0x00bff911, -0x00be03f1,  0x001b701f },
      { -0x01fd3e48,  0x00fd3e8d,  0x00ff65a0, -0x01fd3e48,  0x00fdd8ec }},
     {{ -0x00c44a4d, -0x001d57f3,  0x00cb5918, -0x00c44a4d,  0x00174ef4 },
      { -0x01fd658b,  0x00fd65d0,  0x00ff8513, -0x01fd658b,  0x00fde0bd }},
     {{ -0x00ca9b4a, -0x00160cd0,  0x00d765ac, -0x00ca9b4a,  0x00128d84 },
      { -0x01fd8aa1,  0x00fd8ae6,  0x00ffa422, -0x01fd8aa1,  0x00fde6c4 }},
     {{ -0x00d0f451, -0x000eb865,  0x00e42905, -0x00d0f451,  0x000d1e96 },
      { -0x01fdadaa,  0x00fdadee,  0x00ffc2e9, -0x01fdadaa,  0x00fdeb06 }},
     {{ -0x00d752ba, -0x00075dc2,  0x00f1adf9, -0x00d752ba,  0x0006f445 },
      { -0x01fdcec0,  0x00fdcf05,  0x00ffe17f, -0x01fdcec0,  0x00fded86 }},
     {{ -0x00ddb3d7,  0x00000000,  0x01000000, -0x00ddb3d7,  0x00000000 },
      { -0x01fdee01,  0x00fdee46,  0x01000000, -0x01fdee01,  0x00fdee46 }},
     {{ -0x00e414f4,  0x00075dc2,  0x010f2b41, -0x00e414f4, -0x0007cd7f },
      { -0x01fe0b86,  0x00fe0bcb,  0x01001e84, -0x01fe0b86,  0x00fded47 }},
     {{ -0x00ea735e,  0x000eb865,  0x011f3c9a, -0x00ea735e, -0x00108435 },
      { -0x01fe2768,  0x00fe27ac,  0x01003d26, -0x01fe2768,  0x00fdea86 }},
     {{ -0x00f0cc64,  0x00160cd0,  0x013041af, -0x00f0cc64, -0x001a34df },
      { -0x01fe41bd,  0x00fe4201,  0x01005bff, -0x01fe41bd,  0x00fde603 }},
     {{ -0x00f71d61,  0x001d57f3,  0x014248f0, -0x00f71d61, -0x0024f0fc },
      { -0x01fe5a9b,  0x00fe5ae0,  0x01007b28, -0x01fe5a9b,  0x00fddfb7 }},
     {{ -0x00fd63bd,  0x002496d0,  0x015561a9, -0x00fd63bd, -0x0030cad9 },
      { -0x01fe7217,  0x00fe725c,  0x01009abd, -0x01fe7217,  0x00fdd79f }},
     {{ -0x01039cf1,  0x002bc67c,  0x01699c0f, -0x01039cf1, -0x003dd594 },
      { -0x01fe8845,  0x00fe888a,  0x0100bad7, -0x01fe8845,  0x00fdcdb3 }},
     {{ -0x0109c68a,  0x0032e423,  0x017f094d, -0x0109c68a, -0x004c252a },
      { -0x01fe9d37,  0x00fe9d7c,  0x0100db92, -0x01fe9d37,  0x00fdc1ea }},
     {{ -0x010fde31,  0x0039ed12,  0x0195bb8f, -0x010fde31, -0x005bce7e },
      { -0x01feb0ff,  0x00feb144,  0x0100fd0a, -0x01feb0ff,  0x00fdb43a }},
     {{ -0x0115e1ab,  0x0040deb4,  0x01adc61a, -0x0115e1ab, -0x006ce766 },
      { -0x01fec3ad,  0x00fec3f2,  0x01011f5b, -0x01fec3ad,  0x00fda498 }}
};

static const struct {
	uint32_t rate;
	struct feed_eq_coeff *coeff;
} feed_eq_tab[] = {
	{  44100, eq_44100  },
	{  48000, eq_48000  },
	{  88200, eq_88200  },
	{  96000, eq_96000  },
	{ 176400, eq_176400 },
	{ 192000, eq_192000 },
};

#define FEEDEQ_RATE_MIN		44100
#define FEEDEQ_RATE_MAX		192000

#define FEEDEQ_TAB_SIZE							\
	((int32_t)(sizeof(feed_eq_tab) / sizeof(feed_eq_tab[0])))

static const struct {
	int32_t mul, shift;
} feed_eq_preamp[] = {
	{ 0x00000001, 0x00000003 },	/*  -9.0 dB */
	{ 0x047d66b1, 0x0000001d },	/*  -8.0 dB */
	{ 0x0a14517d, 0x0000001e },	/*  -7.0 dB */
	{ 0x0b504f33, 0x0000001e },	/*  -6.0 dB */
	{ 0x1965fea5, 0x0000001f },	/*  -5.0 dB */
	{ 0x1c823e07, 0x0000001f },	/*  -4.0 dB */
	{ 0x00000001, 0x00000002 },	/*  -3.0 dB */
	{ 0x047d66b1, 0x0000001c },	/*  -2.0 dB */
	{ 0x285145f3, 0x0000001f },	/*  -1.0 dB */
	{ 0x2d413ccd, 0x0000001f },	/*  +0.0 dB */
	{ 0x1965fea5, 0x0000001e },	/*  +1.0 dB */
	{ 0x39047c0f, 0x0000001f },	/*  +2.0 dB */
	{ 0x00000001, 0x00000001 },	/*  +3.0 dB */
	{ 0x47d66b0f, 0x0000001f },	/*  +4.0 dB */
	{ 0x285145f3, 0x0000001e },	/*  +5.0 dB */
	{ 0x2d413ccd, 0x0000001e },	/*  +6.0 dB */
	{ 0x6597fa95, 0x0000001f },	/*  +7.0 dB */
	{ 0x7208f81d, 0x0000001f },	/*  +8.0 dB */
	{ 0x00000001, 0x00000000 },	/*  +9.0 dB */
};

#define FEEDEQ_GAIN_MIN		-9
#define FEEDEQ_GAIN_MAX		9

#define FEEDEQ_GAIN_SHIFT	4
#define FEEDEQ_GAIN_DIV		10
#define FEEDEQ_GAIN_FMASK	0x0000000f
#define FEEDEQ_GAIN_STEP	10

#define FEEDEQ_COEFF_SHIFT	24

/*
 * volume level mapping (0 - 100):
 *
 *	  0  ->    0 ( -9.0 dB)
 *	  1  ->    0 ( -9.0 dB)
 *	  2  ->    0 ( -9.0 dB)
 *	  3  ->    0 ( -9.0 dB)
 *	  4  ->    0 ( -9.0 dB)
 *	  5  ->    0 ( -9.0 dB)
 *	  6  ->    1 ( -8.0 dB)
 *	  7  ->    1 ( -8.0 dB)
 *	  8  ->    1 ( -8.0 dB)
 *	  9  ->    1 ( -8.0 dB)
 *	 10  ->    1 ( -8.0 dB)
 *	 11  ->    2 ( -7.0 dB)
 *	 12  ->    2 ( -7.0 dB)
 *	 13  ->    2 ( -7.0 dB)
 *	 14  ->    2 ( -7.0 dB)
 *	 15  ->    2 ( -7.0 dB)
 *	 16  ->    3 ( -6.0 dB)
 *	 17  ->    3 ( -6.0 dB)
 *	 18  ->    3 ( -6.0 dB)
 *	 19  ->    3 ( -6.0 dB)
 *	 20  ->    3 ( -6.0 dB)
 *	 21  ->    3 ( -6.0 dB)
 *	 22  ->    4 ( -5.0 dB)
 *	 23  ->    4 ( -5.0 dB)
 *	 24  ->    4 ( -5.0 dB)
 *	 25  ->    4 ( -5.0 dB)
 *	 26  ->    4 ( -5.0 dB)
 *	 27  ->    5 ( -4.0 dB)
 *	 28  ->    5 ( -4.0 dB)
 *	 29  ->    5 ( -4.0 dB)
 *	 30  ->    5 ( -4.0 dB)
 *	 31  ->    5 ( -4.0 dB)
 *	 32  ->    6 ( -3.0 dB)
 *	 33  ->    6 ( -3.0 dB)
 *	 34  ->    6 ( -3.0 dB)
 *	 35  ->    6 ( -3.0 dB)
 *	 36  ->    6 ( -3.0 dB)
 *	 37  ->    7 ( -2.0 dB)
 *	 38  ->    7 ( -2.0 dB)
 *	 39  ->    7 ( -2.0 dB)
 *	 40  ->    7 ( -2.0 dB)
 *	 41  ->    7 ( -2.0 dB)
 *	 42  ->    7 ( -2.0 dB)
 *	 43  ->    8 ( -1.0 dB)
 *	 44  ->    8 ( -1.0 dB)
 *	 45  ->    8 ( -1.0 dB)
 *	 46  ->    8 ( -1.0 dB)
 *	 47  ->    8 ( -1.0 dB)
 *	 48  ->    9 ( +0.0 dB)
 *	 49  ->    9 ( +0.0 dB)
 *	 50  ->    9 ( +0.0 dB)
 *	 51  ->    9 ( +0.0 dB)
 *	 52  ->    9 ( +0.0 dB)
 *	 53  ->   10 ( +1.0 dB)
 *	 54  ->   10 ( +1.0 dB)
 *	 55  ->   10 ( +1.0 dB)
 *	 56  ->   10 ( +1.0 dB)
 *	 57  ->   10 ( +1.0 dB)
 *	 58  ->   11 ( +2.0 dB)
 *	 59  ->   11 ( +2.0 dB)
 *	 60  ->   11 ( +2.0 dB)
 *	 61  ->   11 ( +2.0 dB)
 *	 62  ->   11 ( +2.0 dB)
 *	 63  ->   11 ( +2.0 dB)
 *	 64  ->   12 ( +3.0 dB)
 *	 65  ->   12 ( +3.0 dB)
 *	 66  ->   12 ( +3.0 dB)
 *	 67  ->   12 ( +3.0 dB)
 *	 68  ->   12 ( +3.0 dB)
 *	 69  ->   13 ( +4.0 dB)
 *	 70  ->   13 ( +4.0 dB)
 *	 71  ->   13 ( +4.0 dB)
 *	 72  ->   13 ( +4.0 dB)
 *	 73  ->   13 ( +4.0 dB)
 *	 74  ->   14 ( +5.0 dB)
 *	 75  ->   14 ( +5.0 dB)
 *	 76  ->   14 ( +5.0 dB)
 *	 77  ->   14 ( +5.0 dB)
 *	 78  ->   14 ( +5.0 dB)
 *	 79  ->   15 ( +6.0 dB)
 *	 80  ->   15 ( +6.0 dB)
 *	 81  ->   15 ( +6.0 dB)
 *	 82  ->   15 ( +6.0 dB)
 *	 83  ->   15 ( +6.0 dB)
 *	 84  ->   15 ( +6.0 dB)
 *	 85  ->   16 ( +7.0 dB)
 *	 86  ->   16 ( +7.0 dB)
 *	 87  ->   16 ( +7.0 dB)
 *	 88  ->   16 ( +7.0 dB)
 *	 89  ->   16 ( +7.0 dB)
 *	 90  ->   17 ( +8.0 dB)
 *	 91  ->   17 ( +8.0 dB)
 *	 92  ->   17 ( +8.0 dB)
 *	 93  ->   17 ( +8.0 dB)
 *	 94  ->   17 ( +8.0 dB)
 *	 95  ->   18 ( +9.0 dB)
 *	 96  ->   18 ( +9.0 dB)
 *	 97  ->   18 ( +9.0 dB)
 *	 98  ->   18 ( +9.0 dB)
 *	 99  ->   18 ( +9.0 dB)
 *	100  ->   18 ( +9.0 dB)
 */

/*
 * smallest: 0.00000000000000005551115123125783
 *  largest: 4.05056426427985538651910246699117
 */

#endif	/* !_FEEDER_EQ_GEN_H_ */
