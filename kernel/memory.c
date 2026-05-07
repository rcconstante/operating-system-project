#include "memory.h"
#include "screen.h"

#define MEMORY_BLOCK_COUNT 5
#define TOTAL_MEMORY_KB 1024

typedef struct {
    const char *name;
    uint32_t size_kb;
    bool used;
} memory_block_t;

static memory_block_t memory_blocks[MEMORY_BLOCK_COUNT];

void memory_initialize(void)
{
    memory_blocks[0].name = "kernel";
    memory_blocks[0].size_kb = 128;
    memory_blocks[0].used = true;

    memory_blocks[1].name = "screen";
    memory_blocks[1].size_kb = 16;
    memory_blocks[1].used = true;

    memory_blocks[2].name = "shell";
    memory_blocks[2].size_kb = 64;
    memory_blocks[2].used = true;

    memory_blocks[3].name = "process-table";
    memory_blocks[3].size_kb = 48;
    memory_blocks[3].used = true;

    memory_blocks[4].name = "available";
    memory_blocks[4].size_kb = TOTAL_MEMORY_KB - memory_used_kb();
    memory_blocks[4].used = false;
}

uint32_t memory_total_kb(void)
{
    return TOTAL_MEMORY_KB;
}

uint32_t memory_used_kb(void)
{
    uint32_t index;
    uint32_t used = 0;

    for (index = 0; index < MEMORY_BLOCK_COUNT; index++) {
        if (memory_blocks[index].used) {
            used += memory_blocks[index].size_kb;
        }
    }

    return used;
}

uint32_t memory_free_kb(void)
{
    return memory_total_kb() - memory_used_kb();
}

void memory_print_usage(void)
{
    uint32_t index;

    screen_write("Total memory: ");
    screen_write_decimal(memory_total_kb());
    screen_write_line(" KB");

    screen_write("Used memory:  ");
    screen_write_decimal(memory_used_kb());
    screen_write_line(" KB");

    screen_write("Free memory:  ");
    screen_write_decimal(memory_free_kb());
    screen_write_line(" KB");

    screen_write_line("");
    screen_write_line("BLOCK          SIZE(KB)   STATUS");
    screen_write_line("--------------------------------");

    for (index = 0; index < MEMORY_BLOCK_COUNT; index++) {
        screen_write(memory_blocks[index].name);

        if (index == 3) {
            screen_write("  ");
        } else {
            screen_write("          ");
        }

        screen_write_decimal(memory_blocks[index].size_kb);
        screen_write("        ");
        screen_write_line(memory_blocks[index].used ? "USED" : "FREE");
    }
}
