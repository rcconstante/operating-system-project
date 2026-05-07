#ifndef LASALLIANOS_PROCESS_H
#define LASALLIANOS_PROCESS_H

#include "types.h"

typedef enum {
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_WAITING
} process_state_t;

typedef struct {
    uint32_t pid;
    const char *name;
    process_state_t state;
    uint32_t memory_kb;
    uint32_t ticks;
} process_t;

void process_initialize(void);
void process_tick(void);
void process_print_table(void);

#endif
