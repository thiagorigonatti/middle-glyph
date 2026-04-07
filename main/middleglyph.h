//
// Created by thiagorigonatti on 07/04/26.
//

#ifndef MIDDLEGLYPH_H
#define MIDDLEGLYPH_H

#include <stdio.h>

#define OLED_WIDTH  128
#define OLED_HEIGHT 64

extern uint8_t buffer[OLED_WIDTH * OLED_HEIGHT / 8];

void draw_scrolling_row_12(const char *txt, int y, int offset_x);
void draw_static_row_24(const char *txt, int y);

#endif

