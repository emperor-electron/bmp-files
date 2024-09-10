/*
 * Author  : Benjamin Tamayo
 * Date    : September 09, 2024 - 11:10 PM
 * Date    : serial.c
 * Purpose :
 */

#include <stddef.h>
#include <stdlib.h>

#include "serial.h"

uint8_t *serialize_header(bmp_header_t const *header) {
  uint8_t *bytes = (uint8_t *)malloc(sizeof(*header));
  return bytes;
}

uint8_t *serialize_info_header(bmp_info_header_t const *info_header) {
  uint8_t *bytes = (uint8_t *)malloc(sizeof(*info_header));
  return bytes;
}
uint8_t *serialize_color_table(bmp_color_table_t const *color_table) {
  uint8_t *bytes = (uint8_t *)malloc(sizeof(*color_table));
  return bytes;
}
uint8_t *serialize_pixel_data(bmp_pixel_data_t const *pixel_data) {
  uint8_t *bytes = (uint8_t *)malloc(sizeof(*pixel_data));
  return bytes;
}
