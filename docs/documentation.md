# LaSallianOS One-by-One Documentation

This document explains the project in the same order that the operating system runs: boot, kernel initialization, screen output, keyboard input, shell commands, process simulation, and memory simulation.

## 1. Project Purpose

LaSallianOS is an educational 32-bit x86 operating system prototype. It is intentionally small so the main operating system ideas are easy to identify:

- The machine boots through GRUB.
- GRUB loads a freestanding kernel.
- The kernel writes directly to VGA text memory.
- The keyboard is read through PS/2 controller ports.
- The shell accepts basic commands.
- Process and memory management are simulated for demonstration.

## 2. Folder Structure

```txt
LaSallianOS/
|-- boot/
|   |-- boot.asm
|   `-- grub.cfg
|-- kernel/
|   |-- kernel.c
|   |-- kernel.h
|   |-- screen.c
|   |-- screen.h
|   |-- keyboard.c
|   |-- keyboard.h
|   |-- shell.c
|   |-- shell.h
|   |-- process.c
|   |-- process.h
|   |-- memory.c
|   `-- memory.h
|-- drivers/
|   |-- keyboard_driver.c
|   `-- video_driver.c
|-- include/
|   |-- types.h
|   `-- stdio.h
|-- build/
|-- docs/
|   |-- documentation.md
|   |-- screenshots/
|   `-- demo-script.txt
|-- iso/
|   `-- boot/
|       `-- grub/
|           `-- grub.cfg
|-- Makefile
|-- linker.ld
|-- README.md
`-- .gitignore
```

## 3. File-by-File Explanation

### boot/boot.asm

This is the first LaSallianOS code that runs after GRUB loads the kernel. It contains a Multiboot header so GRUB can recognize the kernel image.

Step by step:

1. Defines the Multiboot magic value, flags, and checksum.
2. Reserves a 16 KB stack in the `.bss` section.
3. Sets `ESP` to the top of that stack.
4. Pushes the Multiboot values from GRUB onto the stack.
5. Calls `kernel_main`.
6. Halts forever if the kernel ever returns.

### boot/grub.cfg

This is the GRUB menu configuration.

Step by step:

1. Sets the boot menu timeout to zero.
2. Selects the first menu entry by default.
3. Loads `/boot/kernel.bin` using the Multiboot protocol.
4. Boots the kernel.

### kernel/kernel.c

This is the kernel entry point.

Step by step:

1. Clears and prepares the VGA screen.
2. Prints the boot banner.
3. Checks the Multiboot magic value from GRUB.
4. Initializes memory simulation.
5. Initializes process simulation.
6. Initializes the shell and keyboard input.
7. Starts the shell loop.

### kernel/screen.c

This module handles text output.

Step by step:

1. Maintains the current row and column.
2. Writes characters to VGA text memory through the video driver.
3. Moves the hardware cursor.
4. Handles new lines and backspace.
5. Scrolls the screen when output reaches the bottom.
6. Provides helper functions for decimal and hexadecimal printing.

### kernel/keyboard.c

This module translates raw keyboard scancodes into characters.

Step by step:

1. Polls the keyboard controller until a scancode is ready.
2. Ignores key release events.
3. Tracks left and right Shift keys.
4. Converts scancodes into normal or shifted characters.
5. Builds a command line buffer for the shell.
6. Echoes typed characters to the screen.

### kernel/shell.c

This module implements the command-line interface.

Step by step:

1. Prints the `LaSallianOS>` prompt.
2. Reads one command line from the keyboard.
3. Compares the command with known command names.
4. Runs the matching command handler.
5. Prints an error for unknown commands.
6. Repeats forever until `shutdown` halts the CPU.

Available commands:

| Command | Purpose |
|---|---|
| `help` | Shows the command list |
| `clear` | Clears the screen |
| `about` | Shows operating system information |
| `memory` | Shows simulated memory usage |
| `process` | Shows simulated process table |
| `shutdown` | Halts the system |

### kernel/process.c

This module simulates process management.

Step by step:

1. Creates a fixed process table.
2. Gives each process a PID, name, state, memory size, and tick count.
3. Updates process state each shell cycle.
4. Marks one process as running.
5. Prints the process table when the `process` command is used.

This is a simulation. It does not perform real CPU context switching.

### kernel/memory.c

This module simulates memory management.

Step by step:

1. Sets total simulated memory to 1024 KB.
2. Creates fixed memory blocks for the kernel, screen, shell, and process table.
3. Calculates free memory from the total and used blocks.
4. Prints a memory summary when the `memory` command is used.

This is a simulation. It does not allocate physical pages or virtual memory.

### drivers/video_driver.c

This module performs low-level video work.

Step by step:

1. Points to VGA text memory at `0xB8000`.
2. Writes a character and color attribute into a VGA cell.
3. Reads a VGA cell for scrolling.
4. Updates the hardware cursor through VGA ports `0x3D4` and `0x3D5`.

### drivers/keyboard_driver.c

This module performs low-level keyboard work.

Step by step:

1. Reads the keyboard status port `0x64`.
2. Checks whether the output buffer has data.
3. Reads the scancode from port `0x60`.

### include/types.h

This file defines basic integer and boolean types without depending on the hosted C standard library.

### include/stdio.h

This file exposes small printing helpers used by the kernel.

### linker.ld

This file tells the linker where each part of the kernel should live in memory.

Step by step:

1. Sets `_start` as the entry point.
2. Loads the kernel at the 1 MB address.
3. Keeps the Multiboot header near the beginning of the image.
4. Places `.text`, `.rodata`, `.data`, and `.bss` sections in order.

### Makefile

This file automates the build.

Step by step:

1. Assembles `boot/boot.asm` with NASM.
2. Compiles kernel and driver C files in freestanding mode.
3. Links all object files into `build/kernel.bin`.
4. Copies the kernel and GRUB config into the ISO folder.
5. Runs `grub-mkrescue` to create `build/LaSallianOS.iso`.
6. Runs the ISO in QEMU with `make run`.

## 4. Build Requirements

Install these tools:

- NASM
- i686-elf-gcc
- i686-elf-ld
- GRUB tools with `grub-mkrescue`
- xorriso
- QEMU
- Make

On Windows, WSL is the simplest build environment because GRUB rescue tooling is Linux-oriented.

Ubuntu or Debian setup:

```bash
sudo apt update
sudo apt install nasm qemu-system-x86 grub-pc-bin xorriso make
```

You also need an `i686-elf` cross compiler. If your environment only has normal GCC, the Makefile can be adapted, but a cross compiler is the cleaner option for kernel work.

## 5. Build and Run

Build the ISO:

```bash
make
```

Run the OS:

```bash
make run
```

Expected result:

1. QEMU opens.
2. GRUB immediately loads the kernel.
3. The boot banner appears.
4. The prompt `LaSallianOS>` waits for commands.

## 6. Demo Flow

Use this sequence during a project presentation:

1. Start QEMU with `make run`.
2. Show the boot banner and Multiboot check.
3. Type `help`.
4. Type `about`.
5. Type `memory`.
6. Type `process`.
7. Type `clear`.
8. Type `shutdown`.

## 7. Limitations

LaSallianOS is a prototype. It demonstrates operating system concepts but does not include:

- Real process context switching
- Interrupt descriptor table setup
- Physical memory manager
- Virtual memory
- File system
- User mode
- System calls
- Disk drivers

## 8. Suggested Improvements

Next improvements can be added in this order:

1. Add a Global Descriptor Table setup module.
2. Add an Interrupt Descriptor Table.
3. Replace keyboard polling with keyboard interrupts.
4. Add a programmable interval timer.
5. Add real scheduler ticks.
6. Add a physical memory bitmap allocator.
7. Add a small RAM-backed file system.
