#define CHARGEBAR_WIDTH 64

static const unsigned char chargebar_bmp[] = {
	0x42, 0x4d, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x00,
	0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x80, 0x00,
	0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xe0, 0x07,
	0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x47,
	0x52, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x3f, 0xc0, 0x3f, 0xc0, 0x47,
	0xc0, 0x47, 0xc0, 0x4f, 0xc0, 0x57, 0xc0, 0x57, 0xc0, 0x5f, 0xc0, 0x67,
	0xc0, 0x6f, 0xc0, 0x6f, 0xc0, 0x77, 0xc0, 0x7f, 0xc0, 0x87, 0xc0, 0x8f,
	0xc0, 0x97, 0xc0, 0x9f, 0xc0, 0xa7, 0xc0, 0xaf, 0xc0, 0xb7, 0xc0, 0xbf,
	0xc0, 0xc7, 0xc0, 0xcf, 0xc0, 0xcf, 0xc0, 0xd7, 0xa0, 0xdf, 0x80, 0xe7,
	0x80, 0xe7, 0x60, 0xef, 0x40, 0xf7, 0x40, 0xf7, 0x20, 0xf7, 0x00, 0xff,
	0xc0, 0xfe, 0xa0, 0xfe, 0x60, 0xfe, 0x40, 0xfe, 0x00, 0xfe, 0xc0, 0xfd,
	0x80, 0xfd, 0x40, 0xfd, 0x00, 0xfd, 0xc0, 0xfc, 0x60, 0xfc, 0x20, 0xfc,
	0xe0, 0xfb, 0x80, 0xfb, 0x40, 0xfb, 0x00, 0xfb, 0xc0, 0xfa, 0x60, 0xfa,
	0x20, 0xfa, 0xe0, 0xf9, 0xa0, 0xf9, 0x60, 0xf9, 0x20, 0xf9, 0xe0, 0xf8,
	0xc0, 0xf8, 0x80, 0xf8, 0x60, 0xf8, 0x20, 0xf8, 0x00, 0xf8, 0x00, 0xf8,
	0x00, 0xf8
};

static const unsigned char chargebar_dark_bmp[] = {
	0x42, 0x4d, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x00,
	0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x80, 0x00,
	0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xe0, 0x07,
	0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x24,
	0xc0, 0x24, 0xc0, 0x2c, 0xc0, 0x2c, 0xc0, 0x2c, 0xc0, 0x34, 0xc0, 0x34,
	0xc0, 0x3c, 0xc0, 0x3c, 0xc0, 0x44, 0xc0, 0x44, 0xc0, 0x4c, 0xc0, 0x4c,
	0xc0, 0x54, 0xc0, 0x54, 0xc0, 0x5c, 0xc0, 0x64, 0xc0, 0x64, 0xc0, 0x6c,
	0xc0, 0x6c, 0xc0, 0x74, 0xc0, 0x74, 0xc0, 0x7c, 0xc0, 0x7c, 0xa0, 0x84,
	0xa0, 0x84, 0xa0, 0x8c, 0x80, 0x8c, 0x80, 0x94, 0x60, 0x94, 0x60, 0x94,
	0x40, 0x94, 0x40, 0x9c, 0x20, 0x9c, 0x00, 0x9c, 0xe0, 0x9b, 0xc0, 0x9b,
	0xa0, 0x9b, 0x80, 0x9b, 0x60, 0x9b, 0x20, 0x9b, 0x00, 0x9b, 0xe0, 0x9a,
	0xa0, 0x9a, 0x80, 0x9a, 0x60, 0x9a, 0x20, 0x9a, 0x00, 0x9a, 0xe0, 0x99,
	0xa0, 0x99, 0x80, 0x99, 0x60, 0x99, 0x20, 0x99, 0x00, 0x99, 0xe0, 0x98,
	0xa0, 0x98, 0x80, 0x98, 0x60, 0x98, 0x40, 0x98, 0x40, 0x98, 0x20, 0x98,
	0x00, 0x98, 0x00, 0x98, 0x00, 0x98
};