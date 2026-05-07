#include "kernel.h"
#include "memory.h"
#include "process.h"
#include "screen.h"
#include "shell.h"

static void print_boot_banner(uint32_t multiboot_magic, uint32_t multiboot_info_address)
{
    screen_set_color(SCREEN_COLOR_LIGHT_GREEN, SCREEN_COLOR_BLACK);
    screen_write_line("========================================");
    screen_write_line("          LaSallianOS v1.0");
    screen_write_line("========================================");
    screen_set_color(SCREEN_COLOR_LIGHT_GRAY, SCREEN_COLOR_BLACK);
    screen_write_line("Boot status: GRUB loaded kernel image");

    screen_write("Multiboot magic: ");
    screen_write_hex(multiboot_magic);
    screen_newline();

    screen_write("Multiboot info:  ");
    screen_write_hex(multiboot_info_address);
    screen_newline();

    if (multiboot_magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        screen_write_line("Multiboot check: OK");
    } else {
        screen_set_color(SCREEN_COLOR_LIGHT_RED, SCREEN_COLOR_BLACK);
        screen_write_line("Multiboot check: unexpected magic value");
        screen_set_color(SCREEN_COLOR_LIGHT_GRAY, SCREEN_COLOR_BLACK);
    }

    screen_newline();
}

void kernel_main(uint32_t multiboot_magic, uint32_t multiboot_info_address)
{
    screen_initialize();
    print_boot_banner(multiboot_magic, multiboot_info_address);

    memory_initialize();
    process_initialize();
    shell_initialize();

    screen_write_line("System initialization complete.");
    screen_write_line("Type 'help' to view available commands.");
    shell_run();
}

void kernel_panic(const char *message)
{
    screen_set_color(SCREEN_COLOR_WHITE, SCREEN_COLOR_RED);
    screen_write_line("");
    screen_write_line("KERNEL PANIC");
    screen_write_line(message);

    for (;;) {
        __asm__ volatile ("cli");
        __asm__ volatile ("hlt");
    }
}
