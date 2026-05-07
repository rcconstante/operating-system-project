#include "types.h"

#define VGA_MEMORY_ADDRESS 0xB8000
#define VGA_COMMAND_PORT 0x3D4
#define VGA_DATA_PORT 0x3D5

static volatile uint16_t *const video_memory = (volatile uint16_t *)VGA_MEMORY_ADDRESS;

static inline void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void video_driver_write_cell(uint16_t index, char character, uint8_t color)
{
    video_memory[index] = (uint16_t)((color << 8) | (uint8_t)character);
}

uint16_t video_driver_read_cell(uint16_t index)
{
    return video_memory[index];
}

void video_driver_set_cursor(uint16_t index)
{
    outb(VGA_COMMAND_PORT, 0x0F);
    outb(VGA_DATA_PORT, (uint8_t)(index & 0xFF));
    outb(VGA_COMMAND_PORT, 0x0E);
    outb(VGA_DATA_PORT, (uint8_t)((index >> 8) & 0xFF));
}
