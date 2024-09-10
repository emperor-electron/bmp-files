/*
 * Author  : Benjamin Tamayo
 * Date    : September 09, 2024 - 11:10 PM
 * Date    : serial.h
 * Purpose :
 */

#pragma once

#include <stdint.h>

#include "bmp.h"

uint8_t *serialize_header(bmp_header_t const *header);
uint8_t *serialize_info_header(bmp_info_header_t const *info_header);
uint8_t *serialize_color_table(bmp_color_table_t const *color_table);
uint8_t *serialize_pixel_data(bmp_pixel_data_t const *pixel_data);
