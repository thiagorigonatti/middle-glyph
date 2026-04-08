//
// Created by thiagorigonatti on 07/04/26.
//

#ifndef MIDDLEGLYPH_H
#define MIDDLEGLYPH_H

#include <stdio.h>

#define OLED_WIDTH  128
#define OLED_HEIGHT 64

extern uint8_t buffer[OLED_WIDTH * OLED_HEIGHT / 8];

const uint16_t *get_glyph(const char *character, int *bytes_amount);
void draw_glyph(const int x, const int y, const uint16_t glyph[12], const short size);
void draw_static_row(const char *text, const int y, const short size);
void set_pixel(const int x, const int y);

void draw_scrolling_row(const char *txt, const int y, const int offset_x, const short size);

#endif
