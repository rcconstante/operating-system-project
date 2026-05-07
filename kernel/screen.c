#include "screen.h"
#include "stdio.h"

extern void video_driver_write_cell(uint16_t index, char character, uint8_t color);
extern uint16_t video_driver_read_cell(uint16_t index);
extern void video_driver_set_cursor(uint16_t index);

static uint8_t current_color;
static uint8_t cursor_row;
static uint8_t cursor_column;

static uint8_t make_color(screen_color_t foreground, screen_color_t background)
{
    return (uint8_t)(foreground | (background << 4));
}

static uint16_t cursor_index(void)
{
    return (uint16_t)(cursor_row * VGA_WIDTH + cursor_column);
}

static void update_cursor(void)
{
    video_driver_set_cursor(cursor_index());
}

static void write_blank_at(uint16_t index)
{
    video_driver_write_cell(index, ' ', current_color);
}

static void scroll_if_needed(void)
{
    uint16_t row;
    uint16_t column;

    if (cursor_row < VGA_HEIGHT) {
        return;
    }

    for (row = 1; row < VGA_HEIGHT; row++) {
        for (column = 0; column < VGA_WIDTH; column++) {
            uint16_t from = (uint16_t)(row * VGA_WIDTH + column);
            uint16_t to = (uint16_t)((row - 1) * VGA_WIDTH + column);
            uint16_t cell = video_driver_read_cell(from);
            video_driver_write_cell(to, (char)(cell & 0x00FF), (uint8_t)(cell >> 8));
        }
    }

    for (column = 0; column < VGA_WIDTH; column++) {
        write_blank_at((uint16_t)((VGA_HEIGHT - 1) * VGA_WIDTH + column));
    }

    cursor_row = VGA_HEIGHT - 1;
    cursor_column = 0;
}

void screen_initialize(void)
{
    current_color = make_color(SCREEN_COLOR_LIGHT_GRAY, SCREEN_COLOR_BLACK);
    cursor_row = 0;
    cursor_column = 0;
    screen_clear();
}

void screen_clear(void)
{
    uint16_t index;

    for (index = 0; index < VGA_WIDTH * VGA_HEIGHT; index++) {
        write_blank_at(index);
    }

    cursor_row = 0;
    cursor_column = 0;
    update_cursor();
}

void screen_set_color(screen_color_t foreground, screen_color_t background)
{
    current_color = make_color(foreground, background);
}

void screen_write_char(char character)
{
    if (character == '\n') {
        screen_newline();
        return;
    }

    if (character == '\r') {
        cursor_column = 0;
        update_cursor();
        return;
    }

    if (character == '\b') {
        screen_backspace();
        return;
    }

    video_driver_write_cell(cursor_index(), character, current_color);
    cursor_column++;

    if (cursor_column >= VGA_WIDTH) {
        cursor_column = 0;
        cursor_row++;
    }

    scroll_if_needed();
    update_cursor();
}

void screen_write(const char *text)
{
    uint32_t index = 0;

    if (text == NULL) {
        return;
    }

    while (text[index] != '\0') {
        screen_write_char(text[index]);
        index++;
    }
}

void screen_write_line(const char *text)
{
    screen_write(text);
    screen_newline();
}

void screen_write_decimal(uint32_t value)
{
    char buffer[11];
    int32_t index = 10;

    buffer[index] = '\0';

    if (value == 0) {
        screen_write_char('0');
        return;
    }

    while (value > 0 && index > 0) {
        index--;
        buffer[index] = (char)('0' + (value % 10));
        value /= 10;
    }

    screen_write(&buffer[index]);
}

void screen_write_hex(uint32_t value)
{
    char buffer[11];
    int8_t nibble;
    uint8_t index;

    buffer[0] = '0';
    buffer[1] = 'x';
    buffer[10] = '\0';

    for (index = 0; index < 8; index++) {
        nibble = (int8_t)((value >> ((7 - index) * 4)) & 0xF);
        buffer[index + 2] = (char)(nibble < 10 ? '0' + nibble : 'A' + (nibble - 10));
    }

    screen_write(buffer);
}

void screen_newline(void)
{
    cursor_column = 0;
    cursor_row++;
    scroll_if_needed();
    update_cursor();
}

void screen_backspace(void)
{
    if (cursor_row == 0 && cursor_column == 0) {
        return;
    }

    if (cursor_column == 0) {
        cursor_row--;
        cursor_column = VGA_WIDTH - 1;
    } else {
        cursor_column--;
    }

    write_blank_at(cursor_index());
    update_cursor();
}

int putchar(int character)
{
    screen_write_char((char)character);
    return character;
}

void print(const char *text)
{
    screen_write(text);
}

void println(const char *text)
{
    screen_write_line(text);
}
