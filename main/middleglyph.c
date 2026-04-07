//
// Created by thiagorigonatti on 07/04/26.
//

#include "middleglyph.h"

#define GLYPH_W_12 12
#define GLYPH_H_12 12
#define GLYPH_W_24 24
#define GLYPH_H_24 24

uint8_t buffer[OLED_WIDTH * OLED_HEIGHT / 8];

const uint16_t a[] = {
    0b011100000000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b011111110000,
    0b100000000000,
    0b100000000000,
    0,
    0
};

const uint16_t b[] = {
    0b111111111000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b011100000000,
    0,
    0
};

const uint16_t c[] = {
    0b001111100000,
    0b010000010000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0,
    0
};

const uint16_t d[] = {
    0b011100000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b100010000000,
    0b111111111000,
    0,
    0
};

const uint16_t e[] = {
    0b001111110000,
    0b010010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100011110000,
    0,
    0
};

const uint16_t f[] = {
    0b000010000000,
    0b000010000000,
    0b111111110000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000000001000,
    0b000000001000,
    0,
    0
};

const uint16_t g[] = {
    0b000001110000,
    0b000010001000,
    0b000010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100001110000,
    0b011111111000,
    0,
    0
};

const uint16_t u[] = {
    0b001111111000,
    0b010000000000,
    0b100000000000,
    0b100000000000,
    0b100000000000,
    0b100000000000,
    0b100000000000,
    0b010000000000,
    0b001000000000,
    0b111111111000,
    0,
    0
};

const uint16_t acute[] = {
    0b011100000000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001010,
    0b100010001001,
    0b100010001000,
    0b011111110000,
    0b100000000000,
    0b100000000000,
    0,
    0
};

const uint16_t space[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const uint16_t h[] = {
    0b111111111000,
    0b000010000000,
    0b000001000000,
    0b000001000000,
    0b000001000000,
    0b000001000000,
    0b000001000000,
    0b000001000000,
    0b000001000000,
    0b111110000000,
    0,
    0
};

const uint16_t i[] = {
    0,
    0,
    0,
    0b100000010000,
    0b100000010000,
    0b111111110010,
    0b100000000000,
    0b100000000000,
    0,
    0,
    0,
    0
};

const uint16_t j[] = {
    0,
    0,
    0,
    0b010000000000,
    0b100000000000,
    0b100000010000,
    0b100000010000,
    0b011111110010,
    0,
    0,
    0,
    0
};

const uint16_t k[] = {
    0b111111111000,
    0b000010000000,
    0b000101000000,
    0b000101000000,
    0b001000100000,
    0b001000100000,
    0b010000010000,
    0b010000010000,
    0b100000001000,
    0b100000001000,
    0,
    0
};

const uint16_t l[] = {
    0b000000001000,
    0b000000001000,
    0b011111111000,
    0b100000000000,
    0b100000000000,
    0b100000000000,
    0b100000000000,
    0b100000000000,
    0b100000000000,
    0b100000000000,
    0,
    0
};

const uint16_t m[] = {
    0b000000001000,
    0b000000001000,
    0b111111110000,
    0b000000001000,
    0b000000001000,
    0b000000010000,
    0b000000010000,
    0b000000001000,
    0b000000001000,
    0b111111110000,
    0,
    0
};

const uint16_t n[] = {
    0b000000001000,
    0b000000001000,
    0b111111110000,
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0b111111110000,
    0,
    0
};

const uint16_t o[] = {
    0b001111100000,
    0b010000010000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b010000010000,
    0b001111100000,
    0,
    0
};

const uint16_t p[] = {
    0b111111111000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000001110000,
    0,
    0
};

const uint16_t q[] = {
    0b000001110000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000010001000,
    0b000001110000,
    0b111111111000,
    0,
    0
};

const uint16_t r[] = {
    0b111111111000,
    0b000001000000,
    0b000000100000,
    0b000000010000,
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0,
    0
};

const uint16_t s[] = {
    0b000000100000,
    0b100001010000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b100010001000,
    0b010100001000,
    0b001000000000,
    0,
    0
};

const uint16_t t[] = {
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0b000000001000,
    0b011111111000,
    0b100000001000,
    0b100000001000,
    0b100000001000,
    0b000000001000,
    0b000000001000,
    0,
    0
};

const uint16_t v[] = {
    0b000011111000,
    0b000100000000,
    0b001000000000,
    0b010000000000,
    0b100000000000,
    0b100000000000,
    0b010000000000,
    0b001000000000,
    0b000100000000,
    0b000011111000,
    0,
    0
};

const uint16_t w[] = {
    0b001111111000,
    0b010000000000,
    0b100000000000,
    0b010000000000,
    0b001000000000,
    0b001000000000,
    0b010000000000,
    0b100000000000,
    0b010000000000,
    0b001111111000,
    0,
    0
};

const uint16_t x[] = {
    0b100000001000,
    0b010000010000,
    0b001000100000,
    0b000101000000,
    0b000010000000,
    0b000010000000,
    0b000101000000,
    0b001000100000,
    0b010000010000,
    0b100000001000,
    0,
    0
};

const uint16_t y[] = {
    0b000000001000,
    0b000000010000,
    0b000000100000,
    0b100001000000,
    0b100010000000,
    0b011110000000,
    0b000001000000,
    0b000000100000,
    0b000000010000,
    0b000000001000,
    0,
    0
};

const uint16_t z[] = {
    0b000000001000,
    0b000000001000,
    0b110000001000,
    0b101000001000,
    0b100100001000,
    0b100010001000,
    0b100001001000,
    0b100000101000,
    0b100000011000,
    0b100000000000,
    0,
    0
};

static void clear_line(int y_start, int altura) {
    for (int y = y_start; y < y_start + altura; y++) {
        for (int x = 0; x < OLED_WIDTH; x++) {
            buffer[x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
        }
    }
}

static const uint16_t *get_glyph(const char *cr, int *by) {
    *by = 1;

    if ((unsigned char)cr[0] == 0xC3 && (unsigned char)cr[1] == 0xA1) {
        *by = 2;
        return acute;
    }

    switch (cr[0]) {
        case 'a': return a;
        case 'b': return b;
        case 'c': return c;
        case 'd': return d;
        case 'e': return e;
        case 'f': return f;
        case 'g': return g;
        case 'u': return u;
        case ' ': return space;
        case 'h': return h;
        case 'i': return i;
        case 'j': return j;
        case 'k': return k;
        case 'l': return l;
        case 'm': return m;
        case 'n': return n;
        case 'o': return o;
        case 'p': return p;
        case 'q': return q;
        case 'r': return r;
        case 's': return s;
        case 't': return t;
        case 'v': return v;
        case 'w': return w;
        case 'x': return x;
        case 'y': return y;
        case 'z': return z;
        default:  return NULL;
    }
}

static int calcular_largura_frase(const char *text) {
    int largura = 0;
    int i = 0;
    int b = 0;

    while (text[i] != '\0') {
        get_glyph(&text[i], &b);
        largura += GLYPH_W_12;
        i += b;
    }

    return largura;
}

static void set_pixel(int x, int y) {
    if (x < 0 || x >= OLED_WIDTH || y < 0 || y >= OLED_HEIGHT) {
        return;
    }

    buffer[x + (y / 8) * OLED_WIDTH] |= (1 << (y % 8));
}

static void draw_glyph_12(int x, int y, const uint16_t glyph[12]) {
    for (int c = 0; c < GLYPH_W_12; c++) {
        for (int r = 0; r < GLYPH_H_12; r++) {
            if (glyph[c] & (1 << r)) {
                set_pixel(x + c, y + r);
            }
        }
    }
}

static void draw_glyph_24(int x, int y, const uint16_t glyph[12]) {
    for (int c = 0; c < GLYPH_W_12; c++) {
        for (int r = 0; r < GLYPH_H_12; r++) {
            if (glyph[c] & 1 << r) {
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        set_pixel(x + c * 2 + i, y + r * 2 + j);
                    }
                }
            }
        }
    }
}

static void draw_line_separator(int x, int y_start, int altura) {
    for (int dx = 0; dx < 2; dx++) {
        int xx = x + dx;
        if (xx < 0 || xx >= OLED_WIDTH) {
            continue;
        }

        for (int i = 0; i < altura; i++) {
            set_pixel(xx, y_start + i);
        }
    }
}

void draw_scrolling_row_12(const char *txt, int y, int offset_x) {
    clear_line(y, GLYPH_H_12);

    const int larg = calcular_largura_frase(txt);
    const int espaco = 40;
    const int bloco = larg + espaco;

    if (bloco <= 0) {
        return;
    }

    int scroll = offset_x % bloco;
    if (scroll < 0) {
        scroll += bloco;
    }


    int x_base = OLED_WIDTH - scroll;

    for (int rep = -2; rep <= 2; rep++) {
        int x_vez = x_base + rep * bloco;
        int temp_x = x_vez;
        int i = 0;

        while (txt[i] != '\0') {
            int b = 0;
            const uint16_t *g = get_glyph(&txt[i], &b);

            if (g && (temp_x + GLYPH_W_12 > 0) && (temp_x < OLED_WIDTH)) {
                draw_glyph_12(temp_x, y, g);
            }

            temp_x += GLYPH_W_12;
            i += b;
        }

        int sep_x = x_vez + larg + (espaco / 2);
        if (sep_x + 1 >= 0 && sep_x < OLED_WIDTH) {
            draw_line_separator(sep_x, 20, 2);
        }
    }
}

void draw_static_row_12(const char *txt, int y) {
    clear_line(y, GLYPH_H_12);

    int temp_x = 0;
    int i = 0;

    while (txt[i] != '\0' && temp_x < OLED_WIDTH) {
        int b = 0;
        const uint16_t *g = get_glyph(&txt[i], &b);

        if (g) {
            draw_glyph_12(temp_x, y, g);
        }

        temp_x += GLYPH_W_12;
        i += b;
    }
}

void draw_batery(const char *txt, int y) {
    clear_line(y, GLYPH_H_12);

    int temp_x = 115;
    int i = 0;

    while (txt[i] != '\0' && temp_x < OLED_WIDTH) {
        int b = 0;
        const uint16_t *g = get_glyph(&txt[i], &b);

        if (g) {
            draw_glyph_12(temp_x, y, g);
        }

        temp_x += GLYPH_W_12;
        i += b;
    }
}

void draw_static_row_24(const char *txt, int y) {
    clear_line(y, GLYPH_H_24);

    int temp_x = 0;
    int i = 0;

    while (txt[i] != '\0' && temp_x < OLED_WIDTH) {
        int b = 0;
        const uint16_t *g = get_glyph(&txt[i], &b);

        if (g) {
            draw_glyph_24(temp_x, y, g);
        }

        temp_x += GLYPH_W_24;
        i += b;
    }
}