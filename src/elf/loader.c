unsigned char loader[] = {
  0x55, 0x89, 0xe5, 0x83, 0xec, 0x10, 0xc7, 0x45, 0xfc, 0x67, 0x66, 0x66,
  0x66, 0xc7, 0x45, 0xf8, 0x2a, 0x01, 0x00, 0x00, 0x8b, 0x45, 0xfc, 0x0f,
  0xaf, 0x45, 0xf8, 0x3d, 0xe6, 0x33, 0x33, 0x33, 0x74, 0x06, 0xb8, 0x01,
  0x00, 0x00, 0x00, 0x82, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x82, 0xb8, 0x00,
  0x00, 0x00, 0x00, 0xc9, 0xc3, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x7a, 0x52, 0x00, 0x01, 0x7c, 0x08, 0x01,
  0x1b, 0x0c, 0x04, 0x04, 0x88, 0x01, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0xa8, 0xff, 0xff, 0xff, 0x35, 0x00, 0x00, 0x00,
  0x00, 0x41, 0x0e, 0x08, 0x85, 0x02, 0x42, 0x0d, 0x05, 0x71, 0xc5, 0x0c,
  0x04, 0x04, 0x00, 0x00
};
unsigned int loader_len = 112;
