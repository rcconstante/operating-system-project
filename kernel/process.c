#include "process.h"
#include "screen.h"

#define PROCESS_COUNT 4

static process_t process_table[PROCESS_COUNT];
static uint32_t scheduler_tick;

static const char *state_to_text(process_state_t state)
{
    switch (state) {
    case PROCESS_READY:
        return "READY";
    case PROCESS_RUNNING:
        return "RUNNING";
    case PROCESS_WAITING:
        return "WAITING";
    default:
        return "UNKNOWN";
    }
}

void process_initialize(void)
{
    process_table[0].pid = 1;
    process_table[0].name = "shell";
    process_table[0].state = PROCESS_RUNNING;
    process_table[0].memory_kb = 64;
    process_table[0].ticks = 0;

    process_table[1].pid = 2;
    process_table[1].name = "keyboard";
    process_table[1].state = PROCESS_READY;
    process_table[1].memory_kb = 32;
    process_table[1].ticks = 0;

    process_table[2].pid = 3;
    process_table[2].name = "memory";
    process_table[2].state = PROCESS_WAITING;
    process_table[2].memory_kb = 32;
    process_table[2].ticks = 0;

    process_table[3].pid = 4;
    process_table[3].name = "idle";
    process_table[3].state = PROCESS_READY;
    process_table[3].memory_kb = 16;
    process_table[3].ticks = 0;

    scheduler_tick = 0;
}

void process_tick(void)
{
    uint32_t index;
    uint32_t running_index;

    scheduler_tick++;
    running_index = scheduler_tick % PROCESS_COUNT;

    for (index = 0; index < PROCESS_COUNT; index++) {
        if (process_table[index].state != PROCESS_WAITING) {
            process_table[index].state = PROCESS_READY;
        }
    }

    if (process_table[running_index].state == PROCESS_WAITING) {
        running_index = 0;
    }

    process_table[running_index].state = PROCESS_RUNNING;
    process_table[running_index].ticks++;
}

void process_print_table(void)
{
    uint32_t index;

    screen_write_line("PID   NAME          STATE     MEM(KB)   TICKS");
    screen_write_line("---------------------------------------------");

    for (index = 0; index < PROCESS_COUNT; index++) {
        screen_write_decimal(process_table[index].pid);
        screen_write("     ");
        screen_write(process_table[index].name);

        if (process_table[index].pid == 1 || process_table[index].pid == 4) {
            screen_write("         ");
        } else {
            screen_write("      ");
        }

        screen_write(state_to_text(process_table[index].state));
        screen_write("    ");
        screen_write_decimal(process_table[index].memory_kb);
        screen_write("        ");
        screen_write_decimal(process_table[index].ticks);
        screen_newline();
    }
}
