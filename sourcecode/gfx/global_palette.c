unsigned char global_palette[208] =
{
    0x00, 0x7c, /*   0: rgb(255,   0,   0) */
    0xff, 0xff, /*   1: rgb(255, 255, 255) */
    0x00, 0x00, /*   2: rgb(  0,   0,   0) */
    0x26, 0x39, /*   3: rgb(115,  73,  49) */
    0x10, 0x00, /*   4: rgb(  0,   0, 132) */
    0xe0, 0xff, /*   5: rgb(255, 255,   0) */
    0xe0, 0x83, /*   6: rgb(  0, 255,   0) */
    0xef, 0xbd, /*   7: rgb(123, 125, 123) */
    0xe5, 0x28, /*   8: rgb( 82,  57,  41) */
    0xc6, 0x18, /*   9: rgb( 49,  49,  49) */
    0xdd, 0x82, /*  10: rgb(  0, 182, 239) */
    0x84, 0x10, /*  11: rgb( 33,  32,  33) */
    0x63, 0x94, /*  12: rgb( 41,  28,  25) */
    0x84, 0x14, /*  13: rgb( 41,  32,  33) */
    0x85, 0x94, /*  14: rgb( 41,  36,  41) */
    0xa5, 0x14, /*  15: rgb( 41,  40,  41) */
    0x52, 0x15, /*  16: rgb( 41,  81, 148) */
    0xa4, 0x18, /*  17: rgb( 49,  40,  33) */
    0xa5, 0x18, /*  18: rgb( 49,  40,  41) */
    0xa5, 0x1c, /*  19: rgb( 58,  40,  41) */
    0xe7, 0x1c, /*  20: rgb( 58,  57,  58) */
    0xe7, 0x9c, /*  21: rgb( 58,  61,  58) */
    0x22, 0xa0, /*  22: rgb( 66,  12,  16) */
    0x43, 0x20, /*  23: rgb( 66,  16,  25) */
    0xdc, 0xa1, /*  24: rgb( 66, 117, 230) */
    0x62, 0x24, /*  25: rgb( 74,  24,  16) */
    0x64, 0xa4, /*  26: rgb( 74,  28,  33) */
    0xc6, 0xa4, /*  27: rgb( 74,  53,  49) */
    0xe8, 0xa4, /*  28: rgb( 74,  61,  66) */
    0xe9, 0xa4, /*  29: rgb( 74,  61,  74) */
    0x09, 0xa5, /*  30: rgb( 74,  69,  74) */
    0x29, 0xa5, /*  31: rgb( 74,  77,  74) */
    0xbe, 0xa5, /*  32: rgb( 74, 109, 247) */
    0x63, 0x28, /*  33: rgb( 82,  24,  25) */
    0x4a, 0x29, /*  34: rgb( 82,  81,  82) */
    0xa5, 0x2c, /*  35: rgb( 90,  40,  41) */
    0x6b, 0x2d, /*  36: rgb( 90,  89,  90) */
    0xa5, 0xb0, /*  37: rgb( 99,  45,  41) */
    0x05, 0x31, /*  38: rgb( 99,  65,  41) */
    0x8c, 0x31, /*  39: rgb( 99,  97,  99) */
    0xa5, 0xb4, /*  40: rgb(107,  45,  41) */
    0x28, 0x35, /*  41: rgb(107,  73,  66) */
    0xad, 0xb5, /*  42: rgb(107, 109, 107) */
    0x05, 0x39, /*  43: rgb(115,  65,  41) */
    0x27, 0xb9, /*  44: rgb(115,  77,  58) */
    0x6c, 0xb9, /*  45: rgb(115,  93,  99) */
    0xce, 0x39, /*  46: rgb(115, 113, 115) */
    0xce, 0xb9, /*  47: rgb(115, 117, 115) */
    0x84, 0x3c, /*  48: rgb(123,  32,  33) */
    0x86, 0x3c, /*  49: rgb(123,  32,  49) */
    0xa5, 0xbc, /*  50: rgb(123,  45,  41) */
    0xc6, 0x3c, /*  51: rgb(123,  49,  49) */
    0x44, 0xbd, /*  52: rgb(123,  85,  33) */
    0x46, 0xbd, /*  53: rgb(123,  85,  49) */
    0x8e, 0x3d, /*  54: rgb(123,  97, 115) */
    0xcf, 0x3d, /*  55: rgb(123, 113, 123) */
    0x08, 0x41, /*  56: rgb(132,  65,  66) */
    0x6b, 0xc1, /*  57: rgb(132,  93,  90) */
    0x10, 0xc2, /*  58: rgb(132, 134, 132) */
    0xa5, 0x48, /*  59: rgb(148,  40,  41) */
    0xc6, 0xc8, /*  60: rgb(148,  53,  49) */
    0x26, 0xc9, /*  61: rgb(148,  77,  49) */
    0xa9, 0x49, /*  62: rgb(148, 105,  74) */
    0x52, 0xca, /*  63: rgb(148, 150, 148) */
    0x97, 0xca, /*  64: rgb(148, 166, 189) */
    0x06, 0x4c, /*  65: rgb(156,   0,  49) */
    0xe8, 0xcc, /*  66: rgb(156,  61,  66) */
    0x08, 0x4d, /*  67: rgb(156,  65,  66) */
    0x8d, 0xcd, /*  68: rgb(156, 101, 107) */
    0xa4, 0xcd, /*  69: rgb(156, 109,  33) */
    0x10, 0xce, /*  70: rgb(156, 134, 132) */
    0x31, 0x4e, /*  71: rgb(156, 138, 140) */
    0x32, 0xce, /*  72: rgb(156, 142, 148) */
    0x73, 0x4e, /*  73: rgb(156, 154, 156) */
    0x93, 0x4e, /*  74: rgb(156, 162, 156) */
    0x7c, 0x4f, /*  75: rgb(156, 219, 230) */
    0x84, 0xd0, /*  76: rgb(165,  36,  33) */
    0xa8, 0xd1, /*  77: rgb(165, 109,  66) */
    0x94, 0xd2, /*  78: rgb(165, 166, 165) */
    0xc9, 0xd4, /*  79: rgb(173,  53,  74) */
    0x10, 0x5a, /*  80: rgb(181, 130, 132) */
    0x2e, 0xda, /*  81: rgb(181, 142, 115) */
    0x72, 0x5a, /*  82: rgb(181, 154, 148) */
    0xb5, 0x5a, /*  83: rgb(181, 170, 173) */
    0xb7, 0xda, /*  84: rgb(181, 174, 189) */
    0xd6, 0x5a, /*  85: rgb(181, 178, 181) */
    0x94, 0xde, /*  86: rgb(189, 166, 165) */
    0xf7, 0xde, /*  87: rgb(189, 190, 189) */
    0xd4, 0xe2, /*  88: rgb(197, 182, 165) */
    0x18, 0xe3, /*  89: rgb(197, 198, 197) */
    0x6a, 0x66, /*  90: rgb(206, 154,  82) */
    0xb2, 0xe6, /*  91: rgb(206, 174, 148) */
    0xf7, 0x66, /*  92: rgb(206, 186, 189) */
    0x17, 0x67, /*  93: rgb(206, 194, 189) */
    0x39, 0x67, /*  94: rgb(206, 202, 206) */
    0xb2, 0xea, /*  95: rgb(214, 174, 148) */
    0x3b, 0xeb, /*  96: rgb(214, 206, 222) */
    0x13, 0x6f, /*  97: rgb(222, 194, 156) */
    0x15, 0x6f, /*  98: rgb(222, 194, 173) */
    0x64, 0xf4, /*  99: rgb(239,  28,  33) */
    0x14, 0x77, /* 100: rgb(239, 194, 165) */
    0x37, 0xf7, /* 101: rgb(239, 206, 189) */
    0x0b, 0x7c, /* 102: rgb(255,   0,  90) */
    0x0c, 0xfd, /* 103: rgb(255,  69,  99) */
};
