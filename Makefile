PROJECT := LaSallianOS
BUILD_DIR := build
ISO_DIR := iso
KERNEL_BIN := $(BUILD_DIR)/kernel.bin
ISO_IMAGE := $(BUILD_DIR)/$(PROJECT).iso

ASM ?= nasm
CC ?= i686-elf-gcc
LD ?= i686-elf-ld
GRUB_MKRESCUE ?= grub-mkrescue
QEMU ?= qemu-system-i386

ASMFLAGS := -f elf32
CFLAGS := -std=gnu99 -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -m32 -Wall -Wextra -Iinclude -Ikernel
LDFLAGS := -T linker.ld -m elf_i386 -nostdlib

C_SOURCES := $(wildcard kernel/*.c) $(wildcard drivers/*.c)
C_OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
OBJECTS := $(BUILD_DIR)/boot/boot.o $(C_OBJECTS)

.PHONY: all iso run clean structure

all: iso

structure:
	mkdir -p boot kernel drivers include build docs/screenshots iso/boot/grub

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/boot/boot.o: boot/boot.asm | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_BIN): $(OBJECTS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

iso: $(KERNEL_BIN) boot/grub.cfg
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/kernel.bin
	cp boot/grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	$(GRUB_MKRESCUE) -o $(ISO_IMAGE) $(ISO_DIR)

run: iso
	$(QEMU) -cdrom $(ISO_IMAGE)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(ISO_DIR)/boot/kernel.bin
	rm -f $(ISO_DIR)/boot/grub/grub.cfg
