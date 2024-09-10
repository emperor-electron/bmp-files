/*
 * Author  : Benjamin Tamayo
 * Date    : September 09, 2024 - 10:26 PM
 * Date    : bmp.h
 * Purpose : Working with BMP (bitmaps) files
 */

#pragma once

#include <stdint.h>

// Must be 14 bytes
typedef struct __attribute__((packed)) {
  uint8_t signature[2]; // always "BM"
  uint32_t file_size;   // must be done last
  uint32_t reserved;    // always 0
  uint32_t data_offset; // must be done second to last
} bmp_header_t;

// Must be 40 bytes
typedef struct __attribute__((packed)) {
  uint32_t size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;

  // Bits per Pixel used to store palette entry information. This also
  // identifies in an indirect way the number of possible colors. Possible
  // values are:
  // 1 = monochrome palette. NumColors = 1
  // 4 = 4bit palletized. NumColors = 16
  // 8 = 8bit palletized. NumColors = 256
  // 16 = 16bit RGB. NumColors = 65536
  // 24 = 24bit RGB. NumColors = 16M
  uint16_t bits_per_pixel;

  // Type of Compression
  // 0 = BI_RGB  no compression
  // 1 = BI_RLE8 8bit RLE encoding
  // 2 = BI_RLE4 4bit RLE encoding
  uint32_t compression;
  uint32_t image_size;
  uint32_t x_pixels_per_m;
  uint32_t y_pixels_per_m;
  uint32_t colors_used;
  uint32_t important_colors;
} bmp_info_header_t;

// Variable length -> 4*NumColors bytes
//
// Present only if bmp_info_header less than 8.
// Colors should be ordered by importance.
typedef struct __attribute__((packed)) {
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t reserved;
} bmp_color_table_t;

// Variable length
typedef struct __attribute__((packed)) {
  bmp_color_table_t *data;
} bmp_pixel_data_t;

bmp_header_t create_header(uint32_t width, uint32_t height, uint16_t bpp);
bmp_info_header_t create_info_header(uint32_t width, uint32_t height,
                                     uint16_t bpp);
bmp_color_table_t create_color_table();
bmp_pixel_data_t create_random_pixel_data(uint32_t width, uint32_t height,
                                          uint16_t bpp);
