/*
 * Author  : Benjamin Tamayo
 * Date    : September 09, 2024 - 10:24 PM
 * Date    : bmp.c
 * Purpose : Working with BMP (bitmaps) files
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bmp.h"

int main(int argc, char **argv) {
  printf("Argc: %d\n", argc);
  printf("Argv: %s\n", argv[0]);

  uint32_t width = 1920;
  uint32_t height = 1920;
  uint16_t bits_per_pixel = 8;

  bmp_header_t header = create_header(width, height, bits_per_pixel);
  bmp_info_header_t info_header =
      create_info_header(width, height, bits_per_pixel);
  bmp_pixel_data_t pixel_data =
      create_ramp_pixel_data(width, height, bits_per_pixel);

  FILE *fh = fopen("./test.bmp", "wb");

  if (fh == NULL) {
    perror("fopen");
    return 1;
  }

  size_t bytes_written = fwrite(&header, 1, sizeof(header), fh);

  if (bytes_written == 0) {
    perror("fwrite");
    return 1;
  }

  bytes_written = fwrite(&info_header, 1, sizeof(info_header), fh);

  if (bytes_written == 0) {
    perror("fwrite");
    return 1;
  }

  // Only struct with a pointer to more data
  for (uint32_t x = 0; x < width * height; x++) {
    bytes_written = fwrite(&pixel_data.data[x], 4, 1, fh);

    if (bytes_written == 0) {
      perror("fwrite");
      return 1;
    }
  }

  fclose(fh);

  return 0;
}

bmp_header_t create_header(uint32_t width, uint32_t height, uint16_t bpp) {
  // TODO : Use bpp here to calculate size_of_file
  uint32_t size_of_file = (4 * width * height) + 14 + 40;
  uint32_t data_offset = 0;

  if (bpp < 8) {
    data_offset = 0;
  } else {
    data_offset = 0x36;
  }

  printf("Calculated size of file in bytes: %0d\n", size_of_file);

  bmp_header_t header = {.signature = "BM",
                         .reserved = 0,
                         .file_size = size_of_file,
                         .data_offset = data_offset};

  return header;
}

bmp_info_header_t create_info_header(uint32_t width, uint32_t height,
                                     uint16_t bpp) {

  bmp_info_header_t info_header = {.size = 40,
                                   .planes = 1,
                                   .compression = 0,
                                   .image_size = 0,
                                   .important_colors = 0,
                                   .width = width,
                                   .height = height,
                                   .bits_per_pixel = bpp,
                                   .x_pixels_per_m = height,
                                   .y_pixels_per_m = width};
  return info_header;
}

bmp_color_table_t create_color_table() {
  bmp_color_table_t color_table = {};
  return color_table;
}

bmp_pixel_data_t create_random_pixel_data(uint32_t width, uint32_t height,
                                          uint16_t bpp) {

  bmp_pixel_data_t pixel_data = {.data = NULL};

  bmp_color_table_t *payload =
      (bmp_color_table_t *)malloc(sizeof(bmp_color_table_t) * width * height);
  bmp_color_table_t *beginning_of_payload = payload;

  srand(time(NULL));

  for (uint32_t x = 0; x < width * height; x++) {
    uint8_t random_pixel_color_r = rand() % ((1 << bpp) - 1);
    uint8_t random_pixel_color_g = rand() % ((1 << bpp) - 1);
    uint8_t random_pixel_color_b = rand() % ((1 << bpp) - 1);

    const bmp_color_table_t pixel = {.r = random_pixel_color_r,
                                     .g = random_pixel_color_g,
                                     .b = random_pixel_color_b,
                                     .reserved = 255};

    payload->r = pixel.r;
    payload->g = pixel.g;
    payload->b = pixel.b;
    payload->reserved = pixel.reserved;
    payload++;
  }

  pixel_data.data = beginning_of_payload;

  return pixel_data;
}

bmp_pixel_data_t create_ramp_pixel_data(uint32_t width, uint32_t height,
                                        uint16_t bpp) {
  bmp_pixel_data_t pixel_data = {.data = NULL};

  bmp_color_table_t *payload =
      (bmp_color_table_t *)malloc(sizeof(bmp_color_table_t) * width * height);
  bmp_color_table_t *beginning_of_payload = payload;

  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  for (uint32_t x = 0; x < width * height; x++) {
    r = x % ((1 << bpp) - 1);
    g = 0;
    b = 0;

    payload->r = r;
    payload->g = g;
    payload->b = b;
    payload->reserved = 0;
    payload++;
  }

  pixel_data.data = beginning_of_payload;

  return pixel_data;
}
