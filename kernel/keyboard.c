#include "keyboard.h"
#include "screen.h"

extern bool keyboard_driver_has_data(void);
extern uint8_t keyboard_driver_read_scancode(void);

static bool shift_pressed;

static const char normal_keymap[128] = {
    [0x02] = '1', [0x03] = '2', [0x04] = '3', [0x05] = '4',
    [0x06] = '5', [0x07] = '6', [0x08] = '7', [0x09] = '8',
    [0x0A] = '9', [0x0B] = '0', [0x0C] = '-', [0x0D] = '=',
    [0x0E] = KEYBOARD_BACKSPACE, [0x0F] = '\t',
    [0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r',
    [0x14] = 't', [0x15] = 'y', [0x16] = 'u', [0x17] = 'i',
    [0x18] = 'o', [0x19] = 'p', [0x1A] = '[', [0x1B] = ']',
    [0x1C] = KEYBOARD_ENTER,
    [0x1E] = 'a', [0x1F] = 's', [0x20] = 'd', [0x21] = 'f',
    [0x22] = 'g', [0x23] = 'h', [0x24] = 'j', [0x25] = 'k',
    [0x26] = 'l', [0x27] = ';', [0x28] = '\'', [0x29] = '`',
    [0x2B] = '\\',
    [0x2C] = 'z', [0x2D] = 'x', [0x2E] = 'c', [0x2F] = 'v',
    [0x30] = 'b', [0x31] = 'n', [0x32] = 'm', [0x33] = ',',
    [0x34] = '.', [0x35] = '/', [0x39] = ' '
};

static const char shifted_keymap[128] = {
    [0x02] = '!', [0x03] = '@', [0x04] = '#', [0x05] = '$',
    [0x06] = '%', [0x07] = '^', [0x08] = '&', [0x09] = '*',
    [0x0A] = '(', [0x0B] = ')', [0x0C] = '_', [0x0D] = '+',
    [0x0E] = KEYBOARD_BACKSPACE, [0x0F] = '\t',
    [0x10] = 'Q', [0x11] = 'W', [0x12] = 'E', [0x13] = 'R',
    [0x14] = 'T', [0x15] = 'Y', [0x16] = 'U', [0x17] = 'I',
    [0x18] = 'O', [0x19] = 'P', [0x1A] = '{', [0x1B] = '}',
    [0x1C] = KEYBOARD_ENTER,
    [0x1E] = 'A', [0x1F] = 'S', [0x20] = 'D', [0x21] = 'F',
    [0x22] = 'G', [0x23] = 'H', [0x24] = 'J', [0x25] = 'K',
    [0x26] = 'L', [0x27] = ':', [0x28] = '"', [0x29] = '~',
    [0x2B] = '|',
    [0x2C] = 'Z', [0x2D] = 'X', [0x2E] = 'C', [0x2F] = 'V',
    [0x30] = 'B', [0x31] = 'N', [0x32] = 'M', [0x33] = '<',
    [0x34] = '>', [0x35] = '?', [0x39] = ' '
};

void keyboard_initialize(void)
{
    shift_pressed = false;
}

char keyboard_read_char(void)
{
    for (;;) {
        uint8_t scancode;
        bool released;

        while (!keyboard_driver_has_data()) {
            __asm__ volatile ("pause");
        }

        scancode = keyboard_driver_read_scancode();
        released = (bool)((scancode & 0x80) != 0);
        scancode = (uint8_t)(scancode & 0x7F);

        if (scancode == 0x2A || scancode == 0x36) {
            shift_pressed = (bool)!released;
            continue;
        }

        if (released) {
            continue;
        }

        if (shift_pressed) {
            return shifted_keymap[scancode];
        }

        return normal_keymap[scancode];
    }
}

void keyboard_read_line(char *buffer, uint32_t buffer_size)
{
    uint32_t index = 0;

    if (buffer == NULL || buffer_size == 0) {
        return;
    }

    for (;;) {
        char character = keyboard_read_char();

        if (character == 0) {
            continue;
        }

        if (character == KEYBOARD_ENTER) {
            screen_newline();
            buffer[index] = '\0';
            return;
        }

        if (character == KEYBOARD_BACKSPACE) {
            if (index > 0) {
                index--;
                screen_backspace();
            }
            continue;
        }

        if (character == '\t') {
            character = ' ';
        }

        if (index < buffer_size - 1) {
            buffer[index] = character;
            index++;
            screen_write_char(character);
        }
    }
}
