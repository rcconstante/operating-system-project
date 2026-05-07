#ifndef LASALLIANOS_SCREEN_H
#define LASALLIANOS_SCREEN_H

#include "types.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef enum {
    SCREEN_COLOR_BLACK = 0,
    SCREEN_COLOR_BLUE = 1,
    SCREEN_COLOR_GREEN = 2,
    SCREEN_COLOR_CYAN = 3,
    SCREEN_COLOR_RED = 4,
    SCREEN_COLOR_MAGENTA = 5,
    SCREEN_COLOR_BROWN = 6,
    SCREEN_COLOR_LIGHT_GRAY = 7,
    SCREEN_COLOR_DARK_GRAY = 8,
    SCREEN_COLOR_LIGHT_BLUE = 9,
    SCREEN_COLOR_LIGHT_GREEN = 10,
    SCREEN_COLOR_LIGHT_CYAN = 11,
    SCREEN_COLOR_LIGHT_RED = 12,
    SCREEN_COLOR_LIGHT_MAGENTA = 13,
    SCREEN_COLOR_YELLOW = 14,
    SCREEN_COLOR_WHITE = 15
} screen_color_t;

void screen_initialize(void);
void screen_clear(void);
void screen_set_color(screen_color_t foreground, screen_color_t background);
void screen_write_char(char character);
void screen_write(const char *text);
void screen_write_line(const char *text);
void screen_write_decimal(uint32_t value);
void screen_write_hex(uint32_t value);
void screen_newline(void);
void screen_backspace(void);

#endif
