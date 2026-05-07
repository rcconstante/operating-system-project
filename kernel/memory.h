#ifndef LASALLIANOS_MEMORY_H
#define LASALLIANOS_MEMORY_H

#include "types.h"

void memory_initialize(void);
void memory_print_usage(void);
uint32_t memory_total_kb(void);
uint32_t memory_used_kb(void);
uint32_t memory_free_kb(void);

#endif
