unsigned char loader[] = {
  0x55, 0x89, 0xe5, 0x83, 0xec, 0x10, 0xe8, 0x35, 0x00, 0x00, 0x00, 0xc7,
  0x45, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xeb, 0x19, 0x8b, 0x45, 0xfc, 0x8b,
  0x04, 0x85, 0x1c, 0x01, 0x10, 0x00, 0x3b, 0x45, 0xfc, 0x74, 0x06, 0xb8,
  0x01, 0x00, 0x00, 0x00, 0x82, 0x83, 0x45, 0xfc, 0x01, 0x83, 0x7d, 0xfc,
  0x01, 0x7e, 0xe1, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x82, 0xb8, 0x00, 0x00,
  0x00, 0x00, 0xc9, 0xc3, 0x55, 0x89, 0xe5, 0x83, 0xec, 0x10, 0xc7, 0x45,
  0xf8, 0x00, 0x00, 0x00, 0x00, 0xeb, 0x6d, 0xc7, 0x45, 0xfc, 0x00, 0x00,
  0x00, 0x00, 0xeb, 0x53, 0x8b, 0x45, 0xfc, 0x8b, 0x14, 0x85, 0x1c, 0x01,
  0x10, 0x00, 0x8b, 0x45, 0xfc, 0x83, 0xc0, 0x01, 0x8b, 0x04, 0x85, 0x1c,
  0x01, 0x10, 0x00, 0x39, 0xc2, 0x7e, 0x34, 0x8b, 0x45, 0xfc, 0x8b, 0x04,
  0x85, 0x1c, 0x01, 0x10, 0x00, 0x89, 0x45, 0xf4, 0x8b, 0x45, 0xfc, 0x83,
  0xc0, 0x01, 0x8b, 0x14, 0x85, 0x1c, 0x01, 0x10, 0x00, 0x8b, 0x45, 0xfc,
  0x89, 0x14, 0x85, 0x1c, 0x01, 0x10, 0x00, 0x8b, 0x45, 0xfc, 0x8d, 0x50,
  0x01, 0x8b, 0x45, 0xf4, 0x89, 0x04, 0x95, 0x1c, 0x01, 0x10, 0x00, 0x83,
  0x45, 0xfc, 0x01, 0xb8, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x45, 0xf8, 0x3b,
  0x45, 0xfc, 0x7f, 0xa0, 0x83, 0x45, 0xf8, 0x01, 0x83, 0x7d, 0xf8, 0x01,
  0x7e, 0x8d, 0xc9, 0xc3, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x7a, 0x52, 0x00, 0x01, 0x7c, 0x08, 0x01, 0x1b, 0x0c, 0x04, 0x04,
  0x88, 0x01, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x5c, 0xff, 0xff, 0xff, 0x84, 0x00, 0x00, 0x00, 0x00, 0x41, 0x0e, 0x08,
  0x85, 0x02, 0x42, 0x0d, 0x05, 0x02, 0x80, 0xc5, 0x0c, 0x04, 0x04, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0xfc, 0xfe, 0xff, 0xff,
  0x40, 0x00, 0x00, 0x00, 0x00, 0x41, 0x0e, 0x08, 0x85, 0x02, 0x42, 0x0d,
  0x05, 0x7c, 0xc5, 0x0c, 0x04, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00
};
unsigned int loader_len = 292;
