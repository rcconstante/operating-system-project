# LaSallianOS

LaSallianOS is a simple custom operating system prototype created for an Operating Systems final project. It demonstrates the core flow of a small x86 OS: GRUB boot, kernel initialization, VGA text output, keyboard input, command-line interaction, process management simulation, and memory management simulation.

This repository now contains the complete project structure described in the original proposal, including boot assembly, kernel modules, low-level drivers, build scripts, and step-by-step documentation.

---

## Project Information

| Category | Details |
|---|---|
| Project Name | LaSallianOS |
| Course | Operating Systems |
| School | De La Salle University - Dasmarinas |
| Language | C + NASM Assembly |
| Bootloader | GRUB Multiboot |
| Emulator | QEMU |
| Architecture | 32-bit x86 |

---

## Project Objectives

- Understand how an operating system boots.
- Learn basic freestanding kernel development.
- Implement VGA text mode output.
- Implement basic keyboard input using PS/2 scancodes.
- Build a simple command-line shell.
- Simulate process management.
- Simulate memory management.
- Demonstrate interaction between hardware and software.

---

## Features

### Booting Mechanism

- GRUB-compatible Multiboot header.
- NASM entry point in `boot/boot.asm`.
- Kernel loaded at the 1 MB memory address.
- Boot banner and Multiboot validation output.

### Kernel

- Kernel initialization in `kernel/kernel.c`.
- VGA text mode output.
- Keyboard polling and scancode translation.
- Shell startup.
- Simulated process and memory managers.

### Command-Line Interface

| Command | Description |
|---|---|
| `help` | Displays all available commands |
| `clear` | Clears the screen |
| `about` | Displays OS information |
| `memory` | Displays simulated memory usage |
| `process` | Displays running simulated processes |
| `shutdown` | Halts the system |

### Process Management Simulation

- Fixed process table.
- Process IDs, names, states, memory usage, and tick counts.
- Simple simulated scheduler tick each shell cycle.

### Memory Management Simulation

- Fixed 1024 KB simulated memory model.
- Used and free memory calculation.
- Block table for kernel, screen, shell, process table, and available memory.

---

## Project Folder Structure

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

---

## Technologies Used

| Technology | Purpose |
|---|---|
| C | Freestanding kernel programming |
| NASM Assembly | Multiboot entry point and stack setup |
| GRUB | Boot manager |
| QEMU | Emulation and testing |
| i686-elf-gcc | Cross-compiling C code |
| i686-elf-ld | Linking the kernel |
| Makefile | Build automation |

---

## System Architecture

```txt
+-------------------+
|       GRUB        |
|  Multiboot Loader |
+-------------------+
          |
          v
+-------------------+
|    boot.asm       |
| Stack + Entry     |
+-------------------+
          |
          v
+-------------------+
|      Kernel       |
| Initialization    |
+-------------------+
          |
          v
+-------------------+
|       Shell       |
| Command Interface |
+-------------------+
          |
          v
+-------------------+
| Process + Memory  |
|   Simulations     |
+-------------------+
```

---

## How the System Works

1. GRUB reads `grub.cfg` and loads `kernel.bin`.
2. The Multiboot header in `boot/boot.asm` lets GRUB recognize the kernel.
3. `boot.asm` sets up a stack and calls `kernel_main`.
4. `kernel_main` initializes the screen, memory simulation, process simulation, keyboard, and shell.
5. The shell prints `LaSallianOS>` and waits for typed commands.
6. Commands call the matching module function.

For a full one-by-one explanation, read [docs/documentation.md](docs/documentation.md).

---

## Requirements

Recommended Linux or WSL packages:

```bash
sudo apt update
sudo apt install nasm qemu-system-x86 grub-pc-bin xorriso make
```

You also need an `i686-elf` cross compiler:

- `i686-elf-gcc`
- `i686-elf-ld`

GRUB rescue tooling is easiest to run from Linux or WSL.

---

## Build

```bash
make
```

This will:

1. Assemble `boot/boot.asm`.
2. Compile kernel and driver C files.
3. Link `build/kernel.bin`.
4. Copy the kernel into the ISO folder.
5. Generate `build/LaSallianOS.iso`.

---

## Run

```bash
make run
```

This launches:

```bash
qemu-system-i386 -cdrom build/LaSallianOS.iso
```

---

## Sample Output

```txt
========================================
          LaSallianOS v1.0
========================================
Boot status: GRUB loaded kernel image
Multiboot magic: 0x2BADB002
Multiboot info:  0xXXXXXXXX
Multiboot check: OK

System initialization complete.
Type 'help' to view available commands.
LaSallianOS>
```

---

## Demo Commands

```txt
help
about
memory
process
clear
shutdown
```

Use [docs/demo-script.txt](docs/demo-script.txt) for a presentation sequence.

---

## Key Learning Outcomes

- Basic operating system architecture.
- GRUB and Multiboot loading.
- Freestanding C kernel structure.
- VGA text mode hardware output.
- Keyboard scancode input.
- Shell command dispatch.
- Process table simulation.
- Memory usage simulation.

---

## Limitations

This is an educational prototype. It does not yet include real multitasking, interrupts, paging, user mode, system calls, a file system, or real dynamic memory allocation.

---

## Future Improvements

1. Add GDT setup.
2. Add IDT setup.
3. Replace keyboard polling with interrupts.
4. Add timer interrupts.
5. Add real scheduler ticks.
6. Add a physical memory bitmap allocator.
7. Add a RAM-backed file system.
8. Add user login and command history.

---

## License

This project is intended for educational use.
