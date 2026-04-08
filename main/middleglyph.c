//
// Created by thiagorigonatti on 07/04/26.
//

#include "middleglyph.h"
#include "glyphs.h"

#define GLYPH_W_12 12
#define GLYPH_H_12 12
#define GLYPH_W_24 24
#define GLYPH_H_24 24

#define SIZE_12 12
#define SIZE_24 24

uint8_t buffer[OLED_WIDTH * OLED_HEIGHT / 8];

static void clear_line(const int y_start, const int height) {
    for (int y = y_start; y < y_start + height; y++) {
        for (int x = 0; x < OLED_WIDTH; x++) {
            buffer[x + y / 8 * OLED_WIDTH] &= ~(1 << (y % 8));
        }
    }
}

const uint16_t *get_glyph(const char *character, int *bytes_amount) {
    const unsigned char c0 = character[0];

    if (c0 < 0x80) {
        *bytes_amount = 1;
        switch (c0) {
            case 'a':
            case 'A': return glyph_a_lowercase;
            case 'b':
            case 'B': return glyph_b_lowercase;
            case 'c':
            case 'C': return glyph_c_lowercase;
            case 'd':
            case 'D': return glyph_d_lowercase;
            case 'e':
            case 'E': return glyph_e_lowercase;
            case 'f':
            case 'F': return glyph_f_lowercase;
            case 'g':
            case 'G': return glyph_g_lowercase;
            case 'h':
            case 'H': return glyph_h_lowercase;
            case 'i':
            case 'I': return glyph_i_lowercase;
            case 'j':
            case 'J': return glyph_j_lowercase;
            case 'k':
            case 'K': return glyph_k_lowercase;
            case 'l':
            case 'L': return glyph_l_lowercase;
            case 'm':
            case 'M': return glyph_m_lowercase;
            case 'n':
            case 'N': return glyph_n_lowercase;
            case 'o':
            case 'O': return glyph_o_lowercase;
            case 'p':
            case 'P': return glyph_p_lowercase;
            case 'q':
            case 'Q': return glyph_q_lowercase;
            case 'r':
            case 'R': return glyph_r_lowercase;
            case 's':
            case 'S': return glyph_s_lowercase;
            case 't':
            case 'T': return glyph_t_lowercase;
            case 'u':
            case 'U': return glyph_u_lowercase;
            case 'v':
            case 'V': return glyph_v_lowercase;
            case 'w':
            case 'W': return glyph_w_lowercase;
            case 'x':
            case 'X': return glyph_x_lowercase;
            case 'y':
            case 'Y': return glyph_y_lowercase;
            case 'z':
            case 'Z': return glyph_z_lowercase;
            case ' ':
            default: return NULL;
        }
    }

    if (c0 == 0xC3) {
        *bytes_amount = 2;
        const unsigned char c1 = character[1];
        switch (c1) {
            case 0xA0: return glyph_a_grave_lowercase;
            case 0xA1: return glyph_a_acute_lowercase;
            case 0xA2: return glyph_a_circumflex_lowercase;
            case 0xA3: return glyph_a_tilde_lowercase;
            case 0xA9: return glyph_e_acute_lowercase;
            case 0xAA: return glyph_e_circumflex_lowercase;
            case 0xAD: return glyph_i_acute_lowercase;
            case 0xB3: return glyph_o_acute_lowercase;
            case 0xB4: return glyph_o_circumflex_lowercase;
            case 0xB5: return glyph_o_tilde_lowercase;
            case 0xBA: return glyph_u_acute_lowercase;
            case 0xA7: return glyph_c_cedilla_lowercase;
            default: return NULL;
        }
    }

    return NULL;
}

static int calculate_phrase_width(const char *text, const short size) {
    int width = 0;
    int i = 0;
    int b = 0;

    while (text[i] != '\0') {
        get_glyph(&text[i], &b);
        width += size;
        i += b;
    }

    return width;
}

void set_pixel(const int x, const int y) {
    if (x < 0 || x >= OLED_WIDTH || y < 0 || y >= OLED_HEIGHT) return;
    // y/8 to find which row of bytes the pixel is, example: if y = 10, then 10/8 is 1, so pixel is in row of index 1
    // Multiply row index by screen width to jump to the correct row
    // In the correct row we sum x to jump to the correct column in that row
    // So we do (y%8) to identify the height where the pixel must be enabled, example 10%8 = 2, then height of index 2
    // 1 << 2 is shift left bits of 1 (00000001) twice, then we have 00000100, now the bit of index 2 is enabled
    // Now we do |= (OR operation) with the byte of the buffer, example: 00000001 |= 00000100 is 00000101, this changes
    // a pixel in that page without changing others
    buffer[x + y / 8 * OLED_WIDTH] |= 1 << (y % 8);
}

void draw_glyph(const int x, const int y, const uint16_t glyph[12], const short size) {
    // Iterating over column until end of screen width
    for (int c = 0; c < SIZE_12; c++) {
        // Iterating over row until end of screen height
        for (int r = 0; r < SIZE_12; r++) {
            // 1 << r is doing, if r is 2 means it's in the third row, example: 000000000001 << 2 = 000000000100
            if (glyph[c] & 1 << r) {
                // So, if glyph[c] is 000000001000 then 000000001000 & 000000000100 equals 000000000000 which is false
                // that means set pixel won't be invoked, because there is nothing to change in that

                if (size == SIZE_12) {
                    set_pixel(x + c, y + r);
                    continue;
                }

                if (size == SIZE_24) {
                    for (int i = 0; i < 2; i++) {
                        for (int j = 0; j < 2; j++) {
                            set_pixel(x + c * 2 + i, y + r * 2 + j);
                        }
                    }
                }
            }
        }
    }
}


void draw_static_row(const char *text, const int y, const short size) {
    clear_line(y, size);
    int x = 0;
    int i = 0;
    while (text[i] != '\0' && x < OLED_WIDTH) {
        int b = 0;
        const uint16_t *g = get_glyph(&text[i], &b);
        if (g) {
            draw_glyph(x, y, g, size);
        }
        x += size;
        i += b;
    }
}


static void draw_line_separator(const int x, int y_start, int altura) {
    for (int dx = 0; dx < 2; dx++) {
        const int xx = x + dx;
        if (xx < 0 || xx >= OLED_WIDTH) {
            continue;
        }

        for (int i = 0; i < altura; i++) {
            set_pixel(xx, y_start + i);
        }
    }
}

void draw_scrolling_row(const char *txt, const int y, const int offset_x, const short size) {
    clear_line(y, size);

    const int width = calculate_phrase_width(txt, size);
    const int space = 40;
    const int block = width + space;

    if (block <= 0) {
        return;
    }

    int scroll = offset_x % block;
    if (scroll < 0) {
        scroll += block;
    }

    const int x_base = OLED_WIDTH - scroll;

    for (int rep = -2; rep <= 2; rep++) {
        const int x_vez = x_base + rep * block;
        int temp_x = x_vez;
        int i = 0;

        while (txt[i] != '\0') {
            int b = 0;
            const uint16_t *g = get_glyph(&txt[i], &b);

            if (g && temp_x + size > 0 && temp_x < OLED_WIDTH) {
                draw_glyph(temp_x, y, g, size);
            }

            temp_x += size;
            i += b;
        }

        const int sep_x = x_vez + width + (space / 2);
        if (sep_x + 1 >= 0 && sep_x < OLED_WIDTH) {
            draw_line_separator(sep_x, 20, 2);
        }
    }
}
