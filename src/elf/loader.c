unsigned char loader[] = {
  0x55, 0x89, 0xe5, 0x83, 0xec, 0x10, 0xc7, 0x45, 0xfc, 0x00, 0x00, 0x00,
  0x00, 0xeb, 0x29, 0x8b, 0x45, 0xfc, 0x83, 0xe8, 0x01, 0x50, 0xe8, 0x30,
  0x00, 0x00, 0x00, 0x83, 0xc4, 0x04, 0x89, 0xc2, 0x8b, 0x45, 0xfc, 0x8b,
  0x04, 0x85, 0x40, 0x01, 0x10, 0x00, 0x39, 0xc2, 0x74, 0x06, 0xb8, 0x01,
  0x00, 0x00, 0x00, 0x82, 0x83, 0x45, 0xfc, 0x01, 0x83, 0x7d, 0xfc, 0x0e,
  0x7e, 0xd1, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x82, 0xb8, 0x00, 0x00, 0x00,
  0x00, 0xc9, 0xc3, 0x55, 0x89, 0xe5, 0x83, 0xec, 0x10, 0x83, 0x7d, 0x08,
  0x0c, 0x77, 0x45, 0x8b, 0x45, 0x08, 0xc1, 0xe0, 0x02, 0x05, 0xac, 0x00,
  0x10, 0x00, 0x8b, 0x00, 0xff, 0xe0, 0xc7, 0x45, 0xfc, 0x00, 0x00, 0x00,
  0x00, 0xeb, 0x35, 0xc7, 0x45, 0xfc, 0x02, 0x00, 0x00, 0x00, 0xeb, 0x2c,
  0xc7, 0x45, 0xfc, 0x05, 0x00, 0x00, 0x00, 0xeb, 0x23, 0xc7, 0x45, 0xfc,
  0x08, 0x00, 0x00, 0x00, 0xeb, 0x1a, 0xc7, 0x45, 0xfc, 0x0a, 0x00, 0x00,
  0x00, 0xeb, 0x11, 0xc7, 0x45, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0xeb, 0x08,
  0xc7, 0x45, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x90, 0x8b, 0x45, 0xfc, 0xc9,
  0xc3, 0x00, 0x00, 0x00, 0x66, 0x00, 0x10, 0x00, 0x6f, 0x00, 0x10, 0x00,
  0x78, 0x00, 0x10, 0x00, 0x78, 0x00, 0x10, 0x00, 0x81, 0x00, 0x10, 0x00,
  0x81, 0x00, 0x10, 0x00, 0x81, 0x00, 0x10, 0x00, 0x81, 0x00, 0x10, 0x00,
  0x8a, 0x00, 0x10, 0x00, 0x8a, 0x00, 0x10, 0x00, 0x8a, 0x00, 0x10, 0x00,
  0x8a, 0x00, 0x10, 0x00, 0x93, 0x00, 0x10, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x7a, 0x52, 0x00, 0x01, 0x7c, 0x08, 0x01,
  0x1b, 0x0c, 0x04, 0x04, 0x88, 0x01, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x4b, 0xff, 0xff, 0xff, 0x5e, 0x00, 0x00, 0x00,
  0x00, 0x41, 0x0e, 0x08, 0x85, 0x02, 0x42, 0x0d, 0x05, 0x02, 0x5a, 0xc5,
  0x0c, 0x04, 0x04, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00,
  0xe0, 0xfe, 0xff, 0xff, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x41, 0x0e, 0x08,
  0x85, 0x02, 0x42, 0x0d, 0x05, 0x02, 0x47, 0xc5, 0x0c, 0x04, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff
};
unsigned int loader_len = 380;
