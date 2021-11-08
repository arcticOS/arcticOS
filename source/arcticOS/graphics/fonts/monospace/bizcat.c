// Bizcat by robey (robey.lag.net)
// Licensed under CC-BY 4.0 (http://creativecommons.org/licenses/by/4.0/)

int bizcat[] = {1, 16, 8, 16,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 32 */
   0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 
   0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 33 */
   0x00, 0x00, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 34 */
   0x00, 0x00, 0x00, 0x6c, 0x6c, 0xfe, 0xfe, 0x6c, 
   0x6c, 0xfe, 0xfe, 0x6c, 0x6c, 0x00, 0x00, 0x00, 8, 16, /* 35 */
   0x00, 0x00, 0x30, 0x30, 0x7c, 0xfc, 0xc0, 0xf8, 
   0x7c, 0x0c, 0xfc, 0xf8, 0x30, 0x30, 0x00, 0x00, 8, 16, /* 36 */
   0x00, 0x00, 0x00, 0xe0, 0xa6, 0xee, 0x1c, 0x38, 
   0x70, 0xee, 0xca, 0x0e, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 37 */
   0x00, 0x00, 0x00, 0x70, 0xf8, 0xd8, 0xf8, 0x76, 
   0xfe, 0xdc, 0xcc, 0xfe, 0x76, 0x00, 0x00, 0x00, 8, 16, /* 38 */
   0x00, 0x00, 0x18, 0x18, 0x18, 0x38, 0x30, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 39 */
   0x00, 0x00, 0x18, 0x38, 0x30, 0x70, 0x60, 0x60, 
   0x60, 0x60, 0x70, 0x30, 0x38, 0x18, 0x00, 0x00, 8, 16, /* 40 */
   0x00, 0x00, 0x60, 0x70, 0x30, 0x38, 0x18, 0x18, 
   0x18, 0x18, 0x38, 0x30, 0x70, 0x60, 0x00, 0x00, 8, 16, /* 41 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x38, 
   0xfe, 0xfe, 0x38, 0x6c, 0x6c, 0x00, 0x00, 0x00, 8, 16, /* 42 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 
   0xfc, 0xfc, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 43 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x18, 0x18, 0x18, 0x38, 0x30, 0x00, 8, 16, /* 44 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 45 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 8, 16, /* 46 */
   0x00, 0x00, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 
   0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0x00, 0x00, 8, 16, /* 47 */
   0x00, 0x00, 0x00, 0x7c, 0xfe, 0xc6, 0xce, 0xde, 
   0xf6, 0xe6, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 48 */
   0x00, 0x00, 0x00, 0x18, 0x38, 0x78, 0x58, 0x18, 
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 8, 16, /* 49 */
   0x00, 0x00, 0x00, 0x7c, 0xfe, 0xc6, 0x0e, 0x1c, 
   0x38, 0x70, 0xe0, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 50 */
   0x00, 0x00, 0x00, 0xfe, 0xfe, 0x0c, 0x18, 0x3c, 
   0x0e, 0x06, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 51 */
   0x00, 0x00, 0x00, 0x0c, 0x1c, 0x3c, 0x7c, 0xec, 
   0xcc, 0xfe, 0xfe, 0x0c, 0x0c, 0x00, 0x00, 0x00, 8, 16, /* 52 */
   0x00, 0x00, 0x00, 0xfe, 0xfe, 0xc0, 0xfc, 0xfe, 
   0x06, 0x06, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 53 */
   0x00, 0x00, 0x00, 0x3c, 0x7c, 0xe0, 0xc0, 0xfc, 
   0xfe, 0xc6, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 54 */
   0x00, 0x00, 0x00, 0xfe, 0xfe, 0x06, 0x0e, 0x1c, 
   0x18, 0x38, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 55 */
   0x00, 0x00, 0x00, 0x7c, 0xfe, 0xc6, 0xc6, 0x7c, 
   0xfe, 0xc6, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 56 */
   0x00, 0x00, 0x00, 0x7c, 0xfe, 0xc6, 0xc6, 0xfe, 
   0x7e, 0x06, 0x0e, 0x7c, 0x78, 0x00, 0x00, 0x00, 8, 16, /* 57 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 
   0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 58 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 
   0x00, 0x00, 0x18, 0x18, 0x18, 0x38, 0x30, 0x00, 8, 16, /* 59 */
   0x00, 0x00, 0x00, 0x0c, 0x1c, 0x38, 0x70, 0xe0, 
   0xe0, 0x70, 0x38, 0x1c, 0x0c, 0x00, 0x00, 0x00, 8, 16, /* 60 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 
   0x00, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 61 */
   0x00, 0x00, 0x00, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 
   0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x00, 0x00, 0x00, 8, 16, /* 62 */
   0x00, 0x00, 0x00, 0x7c, 0xfe, 0xc6, 0x06, 0x0e, 
   0x3c, 0x30, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 63 */
   0x00, 0x00, 0x00, 0x7c, 0xfe, 0xc6, 0xd6, 0xde, 
   0xde, 0xdc, 0xc0, 0xfc, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 64 */
   0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x6c, 0x6c, 
   0xc6, 0xfe, 0xfe, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 65 */
   0x00, 0x00, 0x00, 0xfc, 0xfe, 0x66, 0x66, 0x7c, 
   0x7e, 0x66, 0x66, 0xfe, 0xfc, 0x00, 0x00, 0x00, 8, 16, /* 66 */
   0x00, 0x00, 0x00, 0x3c, 0x7e, 0xe6, 0xc0, 0xc0, 
   0xc0, 0xc0, 0xe6, 0x7e, 0x3c, 0x00, 0x00, 0x00, 8, 16, /* 67 */
   0x00, 0x00, 0x00, 0xf8, 0xfc, 0xcc, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xcc, 0xfc, 0xf8, 0x00, 0x00, 0x00, 8, 16, /* 68 */
   0x00, 0x00, 0x00, 0xfe, 0xfe, 0xc0, 0xc0, 0xfc, 
   0xfc, 0xc0, 0xc0, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 69 */
   0x00, 0x00, 0x00, 0xfe, 0xfe, 0xc0, 0xc0, 0xfc, 
   0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 8, 16, /* 70 */
   0x00, 0x00, 0x00, 0x3c, 0x7e, 0xe6, 0xc0, 0xde, 
   0xde, 0xc6, 0xe6, 0x7e, 0x3c, 0x00, 0x00, 0x00, 8, 16, /* 71 */
   0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xfe, 
   0xfe, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 72 */
   0x00, 0x00, 0x00, 0xfc, 0xfc, 0x30, 0x30, 0x30, 
   0x30, 0x30, 0x30, 0xfc, 0xfc, 0x00, 0x00, 0x00, 8, 16, /* 73 */
   0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 
   0x06, 0x06, 0xce, 0xfc, 0x78, 0x00, 0x00, 0x00, 8, 16, /* 74 */
   0x00, 0x00, 0x00, 0xc6, 0xce, 0xdc, 0xf8, 0xf0, 
   0xf0, 0xf8, 0xdc, 0xce, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 75 */
   0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
   0xc0, 0xc0, 0xc0, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 76 */
   0x00, 0x00, 0x00, 0xc6, 0xc6, 0xee, 0xfe, 0xfe, 
   0xd6, 0xd6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 77 */
   0x00, 0x00, 0x00, 0xc6, 0xc6, 0xe6, 0xf6, 0xf6, 
   0xde, 0xde, 0xce, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 78 */
   0x00, 0x00, 0x00, 0x38, 0x7c, 0xee, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 79 */
   0x00, 0x00, 0x00, 0xfc, 0xfe, 0xc6, 0xc6, 0xfe, 
   0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 8, 16, /* 80 */
   0x00, 0x00, 0x00, 0x7c, 0xfe, 0xc6, 0xc6, 0xc6, 
   0xde, 0xde, 0xcc, 0xfe, 0x76, 0x00, 0x00, 0x00, 8, 16, /* 81 */
   0x00, 0x00, 0x00, 0xfc, 0xfe, 0xc6, 0xc6, 0xfe, 
   0xfc, 0xf8, 0xdc, 0xce, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 82 */
   0x00, 0x00, 0x00, 0x7c, 0xfe, 0xc6, 0xe0, 0x78, 
   0x3c, 0x0e, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 83 */
   0x00, 0x00, 0x00, 0xfc, 0xfc, 0x30, 0x30, 0x30, 
   0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 84 */
   0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 85 */
   0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0x6c, 
   0x6c, 0x6c, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 86 */
   0x00, 0x00, 0x00, 0xc6, 0xc6, 0xd6, 0xd6, 0xd6, 
   0xd6, 0xfe, 0x7c, 0x6c, 0x6c, 0x00, 0x00, 0x00, 8, 16, /* 87 */
   0x00, 0x00, 0x00, 0xc6, 0xc6, 0x6c, 0x6c, 0x38, 
   0x38, 0x6c, 0x6c, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 88 */
   0x00, 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x78, 0x78, 
   0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 89 */
   0x00, 0x00, 0x00, 0xfe, 0xfe, 0x06, 0x0c, 0x18, 
   0x30, 0x60, 0xc0, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 90 */
   0x00, 0x00, 0x7c, 0x7c, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x60, 0x60, 0x7c, 0x7c, 0x00, 0x00, 8, 16, /* 91 */
   0x00, 0x00, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 
   0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x00, 0x00, 8, 16, /* 92 */
   0x00, 0x00, 0x7c, 0x7c, 0x0c, 0x0c, 0x0c, 0x0c, 
   0x0c, 0x0c, 0x0c, 0x0c, 0x7c, 0x7c, 0x00, 0x00, 8, 16, /* 93 */
   0x00, 0x00, 0x10, 0x38, 0x7c, 0xee, 0xc6, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 94 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 8, 16, /* 95 */
   0x00, 0x00, 0x30, 0x30, 0x30, 0x38, 0x18, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 96 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x06, 
   0x7e, 0xfe, 0xc6, 0xfe, 0x7e, 0x00, 0x00, 0x00, 8, 16, /* 97 */
   0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xd8, 0xfc, 0xee, 
   0xc6, 0xc6, 0xee, 0xfc, 0xd8, 0x00, 0x00, 0x00, 8, 16, /* 98 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xe6, 
   0xc0, 0xc0, 0xe6, 0x7e, 0x3c, 0x00, 0x00, 0x00, 8, 16, /* 99 */
   0x00, 0x00, 0x06, 0x06, 0x06, 0x36, 0x7e, 0xee, 
   0xc6, 0xc6, 0xee, 0x7e, 0x36, 0x00, 0x00, 0x00, 8, 16, /* 100 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7c, 0xc6, 
   0xfe, 0xfe, 0xc0, 0x7c, 0x3c, 0x00, 0x00, 0x00, 8, 16, /* 101 */
   0x00, 0x00, 0x1e, 0x3e, 0x30, 0xfc, 0xfc, 0x30, 
   0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 102 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x7e, 0xee, 
   0xc6, 0xc6, 0xee, 0x7e, 0x36, 0x0e, 0x7c, 0x78, 8, 16, /* 103 */
   0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xdc, 0xfe, 0xe6, 
   0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 104 */
   0x00, 0x00, 0x18, 0x18, 0x00, 0x78, 0x78, 0x18, 
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 8, 16, /* 105 */
   0x00, 0x00, 0x0c, 0x0c, 0x00, 0x3c, 0x3c, 0x0c, 
   0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x1c, 0xf8, 0xf0, 8, 16, /* 106 */
   0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc6, 0xce, 0xdc, 
   0xf8, 0xf8, 0xdc, 0xce, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 107 */
   0x00, 0x00, 0x78, 0x78, 0x18, 0x18, 0x18, 0x18, 
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 8, 16, /* 108 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0xfe, 0xd6, 
   0xd6, 0xd6, 0xd6, 0xd6, 0xd6, 0x00, 0x00, 0x00, 8, 16, /* 109 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0xfe, 0xe6, 
   0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 110 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7c, 0xee, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 111 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0xfc, 0xee, 
   0xc6, 0xc6, 0xee, 0xfc, 0xd8, 0xc0, 0xc0, 0xc0, 8, 16, /* 112 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x7e, 0xee, 
   0xc6, 0xc6, 0xee, 0x7e, 0x36, 0x06, 0x06, 0x06, 8, 16, /* 113 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0xfe, 0xe6, 
   0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 8, 16, /* 114 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xfe, 0xc0, 
   0xfc, 0x7e, 0x06, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 115 */
   0x00, 0x00, 0x30, 0x30, 0x30, 0xfe, 0xfe, 0x30, 
   0x30, 0x30, 0x30, 0x3e, 0x1e, 0x00, 0x00, 0x00, 8, 16, /* 116 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xce, 0xfe, 0x76, 0x00, 0x00, 0x00, 8, 16, /* 117 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 
   0x6c, 0x6c, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 8, 16, /* 118 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xd6, 
   0xd6, 0xd6, 0xfe, 0x6c, 0x6c, 0x00, 0x00, 0x00, 8, 16, /* 119 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xee, 0x7c, 
   0x38, 0x38, 0x7c, 0xee, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 120 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 
   0x6c, 0x6c, 0x7c, 0x38, 0x18, 0x38, 0xf0, 0xe0, 8, 16, /* 121 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x0c, 
   0x18, 0x30, 0x60, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 122 */
   0x00, 0x00, 0x0e, 0x1e, 0x18, 0x18, 0x38, 0xf0, 
   0xf0, 0x38, 0x18, 0x18, 0x1e, 0x0e, 0x00, 0x00, 8, 16, /* 123 */
   0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
   0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 8, 16, /* 124 */
   0x00, 0x00, 0xe0, 0xf0, 0x30, 0x30, 0x38, 0x1e, 
   0x1e, 0x38, 0x30, 0x30, 0xf0, 0xe0, 0x00, 0x00, 8, 16, /* 125 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0xf6, 0xde, 
   0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 126 */
   0x00, 0x00, 0x00, 0xcc, 0xcc, 0x30, 0x30, 0xcc, 
   0xcc, 0x30, 0x30, 0xcc, 0xcc, 0x00, 0x00, 0x00, 8, 16, /* 127 */
   0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 
   0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 128 */
   0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x78, 
   0xe0, 0xc0, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 129 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x6c, 0xd8, 
   0xd8, 0x6c, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 130 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x6c, 0x36, 
   0x36, 0x6c, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 131 */
   0x00, 0x00, 0x00, 0x18, 0x18, 0x7e, 0xfe, 0xd8, 
   0xd8, 0xfe, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 8, 16, /* 132 */
   0x00, 0x00, 0x3c, 0x7e, 0x66, 0x60, 0xf8, 0xf8, 
   0x60, 0x60, 0xe0, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 133 */
   0x00, 0x00, 0x1e, 0x3e, 0x70, 0xfc, 0xfc, 0x60, 
   0xfc, 0xfc, 0x70, 0x3e, 0x1e, 0x00, 0x00, 0x00, 8, 16, /* 134 */
   0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x78, 0xfc, 0xfc, 
   0x30, 0xfc, 0xfc, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 135 */
   0x00, 0x00, 0xfe, 0xfe, 0x0c, 0xfe, 0xfe, 0x0c, 
   0xfc, 0xf8, 0x1c, 0x0e, 0x06, 0x00, 0x00, 0x00, 8, 16, /* 136 */
   0x00, 0x38, 0x7c, 0x6c, 0x7c, 0x38, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 137 */
   0x00, 0x00, 0x00, 0x00, 0xc6, 0xee, 0x7c, 0x38, 
   0x38, 0x7c, 0xee, 0xc6, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 138 */
   0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0xfc, 
   0xfc, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 139 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7c, 0x7c, 
   0x7c, 0x7c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 140 */
   0x00, 0xea, 0x4e, 0x4e, 0x4a, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 141 */
   0x00, 0x00, 0x38, 0x7c, 0xc6, 0xb2, 0xaa, 0xb2, 
   0xaa, 0xaa, 0xc6, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 142 */
   0x00, 0x00, 0x38, 0x7c, 0xc6, 0x82, 0xba, 0xa2, 
   0xba, 0x82, 0xc6, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 143 */
   0x00, 0x00, 0x00, 0x1e, 0x3e, 0x78, 0xf8, 0xde, 
   0xde, 0xf8, 0xf8, 0xde, 0xde, 0x00, 0x00, 0x00, 8, 16, /* 144 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xfe, 0x36, 
   0x7e, 0xfc, 0xd8, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 145 */
   0x00, 0x00, 0x00, 0x7e, 0xfe, 0xd8, 0xd8, 0xde, 
   0xde, 0xd8, 0xd8, 0xfe, 0x7e, 0x00, 0x00, 0x00, 8, 16, /* 146 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xfe, 0xd6, 
   0xde, 0xdc, 0xd8, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 147 */
   0x00, 0x38, 0x0c, 0x3c, 0x6c, 0x3c, 0x00, 0x7c, 
   0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 148 */
   0x00, 0x38, 0x6c, 0x6c, 0x6c, 0x38, 0x00, 0x7c, 
   0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 8, 16, /* 149 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0xdb, 0xdb, 0x00, 0x00, 0x00, 8, 16, /* 150 */
   0x70, 0x7c, 0x1c, 0x10, 0x38, 0x38, 0x6c, 0x6c, 
   0xc6, 0xfe, 0xfe, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 151 */
   0x1c, 0x7c, 0x70, 0x10, 0x38, 0x38, 0x6c, 0x6c, 
   0xc6, 0xfe, 0xfe, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 152 */
   0x38, 0x7c, 0xee, 0x10, 0x38, 0x38, 0x6c, 0x6c, 
   0xc6, 0xfe, 0xfe, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 153 */
   0x76, 0xfe, 0xdc, 0x10, 0x38, 0x38, 0x6c, 0x6c, 
   0xc6, 0xfe, 0xfe, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 154 */
   0x00, 0x6c, 0x6c, 0x10, 0x38, 0x38, 0x6c, 0x6c, 
   0xc6, 0xfe, 0xfe, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 155 */
   0x38, 0x6c, 0x6c, 0x38, 0x38, 0x38, 0x6c, 0x6c, 
   0xc6, 0xfe, 0xfe, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 156 */
   0x70, 0x7c, 0x1c, 0x00, 0xfe, 0xfe, 0xc0, 0xfc, 
   0xfc, 0xc0, 0xc0, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 157 */
   0x1c, 0x7c, 0x70, 0x00, 0xfe, 0xfe, 0xc0, 0xfc, 
   0xfc, 0xc0, 0xc0, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 158 */
   0x38, 0x7c, 0xee, 0x00, 0xfe, 0xfe, 0xc0, 0xfc, 
   0xfc, 0xc0, 0xc0, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 159 */
   0x00, 0x6c, 0x6c, 0x00, 0xfe, 0xfe, 0xc0, 0xfc, 
   0xfc, 0xc0, 0xc0, 0xfe, 0xfe, 0x00, 0x00, 0x00, 8, 16, /* 160 */
   0xe0, 0xf8, 0x38, 0x00, 0xfc, 0xfc, 0x30, 0x30, 
   0x30, 0x30, 0x30, 0xfc, 0xfc, 0x00, 0x00, 0x00, 8, 16, /* 161 */
   0x1c, 0x7c, 0x70, 0x00, 0xfc, 0xfc, 0x30, 0x30, 
   0x30, 0x30, 0x30, 0xfc, 0xfc, 0x00, 0x00, 0x00, 8, 16, /* 162 */
   0x30, 0x78, 0xcc, 0x00, 0xfc, 0xfc, 0x30, 0x30, 
   0x30, 0x30, 0x30, 0xfc, 0xfc, 0x00, 0x00, 0x00, 8, 16, /* 163 */
   0x00, 0xcc, 0xcc, 0x00, 0xfc, 0xfc, 0x30, 0x30, 
   0x30, 0x30, 0x30, 0xfc, 0xfc, 0x00, 0x00, 0x00, 8, 16, /* 164 */
   0x00, 0x00, 0x00, 0x3c, 0x7e, 0xe6, 0xc0, 0xc0, 
   0xc0, 0xc0, 0xe6, 0x7e, 0x3c, 0x18, 0x78, 0x30, 8, 16, /* 165 */
   0x76, 0xfe, 0xdc, 0x00, 0xc6, 0xc6, 0xe6, 0xf6, 
   0xfe, 0xde, 0xce, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 166 */
   0x70, 0x7c, 0x1c, 0x00, 0x38, 0x7c, 0xee, 0xc6, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 167 */
   0x1c, 0x7c, 0x70, 0x00, 0x38, 0x7c, 0xee, 0xc6, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 168 */
   0x38, 0x7c, 0xee, 0x00, 0x38, 0x7c, 0xee, 0xc6, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 169 */
   0x76, 0xfe, 0xdc, 0x00, 0x38, 0x7c, 0xee, 0xc6, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 170 */
   0x00, 0x6c, 0x6c, 0x00, 0x38, 0x7c, 0xee, 0xc6, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 171 */
   0x00, 0x00, 0x00, 0x36, 0x7e, 0xec, 0xde, 0xde, 
   0xf6, 0xf6, 0x6e, 0xfc, 0xd8, 0x00, 0x00, 0x00, 8, 16, /* 172 */
   0x70, 0x7c, 0x1c, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 173 */
   0x1c, 0x7c, 0x70, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 174 */
   0x38, 0x7c, 0xee, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 175 */
   0x00, 0x6c, 0x6c, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00, 8, 16, /* 176 */
   0x38, 0xf8, 0xe0, 0x00, 0xcc, 0xcc, 0xcc, 0xfc, 
   0x78, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 177 */
   0x00, 0xcc, 0xcc, 0x00, 0xcc, 0xcc, 0xcc, 0x78, 
   0x78, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 8, 16, /* 178 */
   0x00, 0x00, 0x00, 0x78, 0x7c, 0x6c, 0x66, 0xf6, 
   0xf6, 0x66, 0x6c, 0x7c, 0x78, 0x00, 0x00, 0x00, 8, 16, /* 179 */
   0x00, 0x00, 0x00, 0xc0, 0xc0, 0xfc, 0xfe, 0xc6, 
   0xc6, 0xfe, 0xfc, 0xc0, 0xc0, 0x00, 0x00, 0x00, 8, 16, /* 180 */
   0x00, 0x00, 0x00, 0x7e, 0xfe, 0xcc, 0xd8, 0xdc, 
   0xce, 0xc6, 0xc6, 0xde, 0xdc, 0x00, 0x00, 0x00, 8, 16, /* 181 */
   0x00, 0x70, 0x7c, 0x1c, 0x00, 0x3c, 0x7e, 0x06, 
   0x7e, 0xfe, 0xc6, 0xfe, 0x7e, 0x00, 0x00, 0x00, 8, 16, /* 182 */
   0x00, 0x1c, 0x7c, 0x70, 0x00, 0x3c, 0x7e, 0x06, 
   0x7e, 0xfe, 0xc6, 0xfe, 0x7e, 0x00, 0x00, 0x00, 8, 16, /* 183 */
   0x00, 0x38, 0x7c, 0xee, 0x00, 0x3c, 0x7e, 0x06, 
   0x7e, 0xfe, 0xc6, 0xfe, 0x7e, 0x00, 0x00, 0x00, 8, 16, /* 184 */
   0x00, 0x76, 0xfe, 0xdc, 0x00, 0x3c, 0x7e, 0x06, 
   0x7e, 0xfe, 0xc6, 0xfe, 0x7e, 0x00, 0x00, 0x00, 8, 16, /* 185 */
   0x00, 0x00, 0x6c, 0x6c, 0x00, 0x3c, 0x7e, 0x06, 
   0x7e, 0xfe, 0xc6, 0xfe, 0x7e, 0x00, 0x00, 0x00, 8, 16, /* 186 */
   0x00, 0x38, 0x6c, 0x6c, 0x38, 0x3c, 0x7e, 0x06, 
   0x7e, 0xfe, 0xc6, 0xfe, 0x7e, 0x00, 0x00, 0x00, 8, 16, /* 187 */
   0x00, 0x70, 0x7c, 0x1c, 0x00, 0x38, 0x7c, 0xc6, 
   0xfe, 0xfe, 0xc0, 0x7c, 0x3c, 0x00, 0x00, 0x00, 8, 16, /* 188 */
   0x00, 0x1c, 0x7c, 0x70, 0x00, 0x38, 0x7c, 0xc6, 
   0xfe, 0xfe, 0xc0, 0x7c, 0x3c, 0x00, 0x00, 0x00, 8, 16, /* 189 */
   0x00, 0x38, 0x7c, 0xee, 0x00, 0x38, 0x7c, 0xc6, 
   0xfe, 0xfe, 0xc0, 0x7c, 0x3c, 0x00, 0x00, 0x00, 8, 16, /* 190 */
   0x00, 0x00, 0x6c, 0x6c, 0x00, 0x38, 0x7c, 0xc6, 
   0xfe, 0xfe, 0xc0, 0x7c, 0x3c, 0x00, 0x00, 0x00, 8, 16, /* 191 */
   0x00, 0x70, 0x7c, 0x1c, 0x00, 0x78, 0x78, 0x18, 
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 8, 16, /* 192 */
   0x00, 0x1c, 0x7c, 0x70, 0x00, 0x78, 0x78, 0x18, 
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 8, 16, /* 193 */
   0x00, 0x38, 0x7c, 0xee, 0x00, 0x78, 0x78, 0x18, 
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 8, 16, /* 194 */
   0x00, 0x00, 0x6c, 0x6c, 0x00, 0x78, 0x78, 0x18, 
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 8, 16, /* 195 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xe6, 
   0xc0, 0xc0, 0xe6, 0x7e, 0x3c, 0x18, 0x78, 0x30, 8, 16, /* 196 */
   0x00, 0x76, 0xfe, 0xdc, 0x00, 0xdc, 0xfe, 0xe6, 
   0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 8, 16, /* 197 */
   0x00, 0x70, 0x7c, 0x1c, 0x00, 0x38, 0x7c, 0xee, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 198 */
   0x00, 0x1c, 0x7c, 0x70, 0x00, 0x38, 0x7c, 0xee, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 199 */
   0x00, 0x38, 0x7c, 0xee, 0x00, 0x38, 0x7c, 0xee, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 200 */
   0x00, 0x76, 0xfe, 0xdc, 0x00, 0x38, 0x7c, 0xee, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 201 */
   0x00, 0x00, 0x6c, 0x6c, 0x00, 0x38, 0x7c, 0xee, 
   0xc6, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 202 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x7e, 0xec, 
   0xde, 0xf6, 0x6e, 0xfc, 0xd8, 0x00, 0x00, 0x00, 8, 16, /* 203 */
   0x00, 0x70, 0x7c, 0x1c, 0x00, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xce, 0xfe, 0x76, 0x00, 0x00, 0x00, 8, 16, /* 204 */
   0x00, 0x1c, 0x7c, 0x70, 0x00, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xce, 0xfe, 0x76, 0x00, 0x00, 0x00, 8, 16, /* 205 */
   0x00, 0x38, 0x7c, 0xee, 0x00, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xce, 0xfe, 0x76, 0x00, 0x00, 0x00, 8, 16, /* 206 */
   0x00, 0x00, 0x6c, 0x6c, 0x00, 0xc6, 0xc6, 0xc6, 
   0xc6, 0xc6, 0xce, 0xfe, 0x76, 0x00, 0x00, 0x00, 8, 16, /* 207 */
   0x00, 0x1c, 0x7c, 0x70, 0x00, 0xc6, 0xc6, 0xc6, 
   0x6c, 0x6c, 0x7c, 0x38, 0x18, 0x38, 0xf0, 0xe0, 8, 16, /* 208 */
   0x00, 0x00, 0x6c, 0x6c, 0x00, 0xc6, 0xc6, 0xc6, 
   0x6c, 0x6c, 0x7c, 0x38, 0x18, 0x38, 0xf0, 0xe0, 8, 16, /* 209 */
   0x00, 0x00, 0x30, 0x3c, 0x78, 0x1c, 0x3c, 0x7e, 
   0xee, 0xc6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00, 8, 16, /* 210 */
   0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xd8, 0xfc, 0xee, 
   0xc6, 0xc6, 0xee, 0xfc, 0xd8, 0xc0, 0xc0, 0xc0, 8, 16, /* 211 */
   0x00, 0x00, 0x78, 0xfc, 0xcc, 0xcc, 0xd8, 0xdc, 
   0xce, 0xc6, 0xc6, 0xde, 0xdc, 0x00, 0x00, 0x00, 8, 16, /* 212 */
};