#ifndef LASALLIANOS_KERNEL_H
#define LASALLIANOS_KERNEL_H

#include "types.h"

#define LASALLIANOS_NAME "LaSallianOS"
#define LASALLIANOS_VERSION "1.0"
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

void kernel_main(uint32_t multiboot_magic, uint32_t multiboot_info_address);
void kernel_panic(const char *message);

#endif
