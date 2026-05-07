#include "kernel.h"
#include "keyboard.h"
#include "memory.h"
#include "process.h"
#include "screen.h"
#include "shell.h"
#include "types.h"

#define SHELL_BUFFER_SIZE 80

static char command_buffer[SHELL_BUFFER_SIZE];

static bool string_equals(const char *left, const char *right)
{
    uint32_t index = 0;

    while (left[index] != '\0' && right[index] != '\0') {
        if (left[index] != right[index]) {
            return false;
        }
        index++;
    }

    return (bool)(left[index] == '\0' && right[index] == '\0');
}

static bool string_is_empty(const char *value)
{
    return (bool)(value[0] == '\0');
}

static void print_prompt(void)
{
    screen_set_color(SCREEN_COLOR_LIGHT_GREEN, SCREEN_COLOR_BLACK);
    screen_write("LaSallianOS");
    screen_set_color(SCREEN_COLOR_LIGHT_GRAY, SCREEN_COLOR_BLACK);
    screen_write("> ");
}

static void command_help(void)
{
    screen_write_line("Available commands:");
    screen_write_line("  help     - Display all available commands");
    screen_write_line("  clear    - Clear the screen");
    screen_write_line("  about    - Display operating system information");
    screen_write_line("  memory   - Display simulated memory usage");
    screen_write_line("  process  - Display simulated process table");
    screen_write_line("  shutdown - Halt the simulated system");
}

static void command_about(void)
{
    screen_write_line(LASALLIANOS_NAME " " LASALLIANOS_VERSION);
    screen_write_line("Educational x86 operating system prototype.");
    screen_write_line("Core modules: boot, kernel, screen, keyboard, shell, process, memory.");
}

static void command_shutdown(void)
{
    screen_write_line("Saving simulated state...");
    screen_write_line("System halted. You may close QEMU.");

    for (;;) {
        __asm__ volatile ("cli");
        __asm__ volatile ("hlt");
    }
}

static void execute_command(const char *command)
{
    if (string_is_empty(command)) {
        return;
    }

    if (string_equals(command, "help")) {
        command_help();
    } else if (string_equals(command, "clear")) {
        screen_clear();
    } else if (string_equals(command, "about")) {
        command_about();
    } else if (string_equals(command, "memory")) {
        memory_print_usage();
    } else if (string_equals(command, "process")) {
        process_print_table();
    } else if (string_equals(command, "shutdown")) {
        command_shutdown();
    } else {
        screen_set_color(SCREEN_COLOR_LIGHT_RED, SCREEN_COLOR_BLACK);
        screen_write("Unknown command: ");
        screen_write_line(command);
        screen_set_color(SCREEN_COLOR_LIGHT_GRAY, SCREEN_COLOR_BLACK);
        screen_write_line("Type 'help' to view valid commands.");
    }
}

void shell_initialize(void)
{
    keyboard_initialize();
}

void shell_run(void)
{
    for (;;) {
        process_tick();
        print_prompt();
        keyboard_read_line(command_buffer, SHELL_BUFFER_SIZE);
        execute_command(command_buffer);
    }
}
