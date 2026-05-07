#include "types.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_OUTPUT_FULL 0x01

static inline uint8_t inb(uint16_t port)
{
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

bool keyboard_driver_has_data(void)
{
    return (bool)((inb(KEYBOARD_STATUS_PORT) & KEYBOARD_OUTPUT_FULL) != 0);
}

uint8_t keyboard_driver_read_scancode(void)
{
    return inb(KEYBOARD_DATA_PORT);
}
