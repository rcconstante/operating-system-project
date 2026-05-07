# LaSallianOS

A simple custom operating system prototype developed for the Operating Systems Final Project at De La Salle University – Dasmariñas (DLSU-D).

LaSallianOS demonstrates core operating system concepts including booting, kernel initialization, command-line interaction, process management simulation, and memory management simulation.

---

# Project Information

| Category | Details |
|---|---|
| Project Name | LaSallianOS |
| Course | Operating Systems |
| School | De La Salle University – Dasmariñas |
| Language | C + NASM Assembly |
| Bootloader | GRUB |
| Emulator | QEMU |
| Architecture | x86 |

---

# Project Objectives

The main objectives of this project are:

- Understand how operating systems boot
- Learn basic kernel development
- Implement a simple command-line interface
- Simulate process management
- Simulate memory management
- Demonstrate interaction between hardware and software

---

# Features

## Booting Mechanism
- Custom bootloader
- Boots into a simple kernel
- Displays boot messages

## Kernel
- Kernel initialization
- VGA text mode output
- Keyboard input handling

## Command-Line Interface
Available commands:

| Command | Description |
|---|---|
| help | Displays all available commands |
| clear | Clears the screen |
| about | Displays OS information |
| memory | Displays simulated memory usage |
| process | Displays running processes |
| shutdown | Simulates system shutdown |

## Process Management
- Simulated process table
- Displays running tasks
- Demonstrates multitasking concepts

## Memory Management
- Simulated memory allocation
- Displays used and available memory
- Demonstrates memory tracking concepts

---

# Project Folder Structure

```txt
LaSallianOS/
│
├── boot/
│   ├── boot.asm
│   └── grub.cfg
│
├── kernel/
│   ├── kernel.c
│   ├── kernel.h
│   ├── screen.c
│   ├── screen.h
│   ├── keyboard.c
│   ├── keyboard.h
│   ├── shell.c
│   ├── shell.h
│   ├── process.c
│   ├── process.h
│   ├── memory.c
│   └── memory.h
│
├── drivers/
│   ├── keyboard_driver.c
│   └── video_driver.c
│
├── include/
│   ├── types.h
│   └── stdio.h
│
├── build/
│
├── docs/
│   ├── documentation.md
│   ├── screenshots/
│   └── demo-script.txt
│
├── iso/
│   └── boot/
│       └── grub/
│           └── grub.cfg
│
├── Makefile
├── linker.ld
├── README.md
└── .gitignore
```

---

# Technologies Used

| Technology | Purpose |
|---|---|
| C | Kernel programming |
| NASM Assembly | Bootloader |
| GRUB | Boot manager |
| QEMU | OS emulation/testing |
| GCC | Compilation |
| Makefile | Build automation |

---

# System Architecture

```txt
+-------------------+
|   Bootloader      |
|  (GRUB + NASM)    |
+-------------------+
          ↓
+-------------------+
|      Kernel       |
|   (Kernel Core)   |
+-------------------+
          ↓
+-------------------+
| Command Interface |
|      Shell        |
+-------------------+
          ↓
+-------------------+
| Process Manager   |
+-------------------+
          ↓
+-------------------+
| Memory Manager    |
+-------------------+
```

---

# How the System Works

## 1. Boot Process
The bootloader initializes the operating system and loads the kernel into memory.

## 2. Kernel Initialization
The kernel initializes:
- Screen output
- Keyboard input
- Memory manager
- Process manager
- Command-line shell

## 3. Shell Execution
The shell waits for user commands and executes the corresponding functions.

---

# Installation and Setup

## Requirements

Install the following tools:

- NASM
- GCC
- GRUB
- QEMU
- Make

---

# Windows Setup

Recommended:
- MinGW GCC
- NASM Installer
- QEMU for Windows

---

# Linux Setup

Ubuntu/Debian:

```bash
sudo apt update
sudo apt install nasm gcc qemu grub-pc-bin xorriso make
```

---

# Building the Operating System

Run:

```bash
make
```

This will:
- Assemble the bootloader
- Compile the kernel
- Link the kernel
- Generate the bootable ISO

---

# Running the Operating System

Run using QEMU:

```bash
qemu-system-x86_64 -cdrom LaSallianOS.iso
```

---

# Sample Output

```txt
===========================
      LaSallianOS v1.0
===========================

System Boot Successful

> help

Commands:
help
clear
about
memory
process
shutdown
```

---

# Sample Commands

## Help Command

```txt
> help
```

Displays all available commands.

---

## Memory Command

```txt
> memory
```

Displays simulated memory usage.

Example:

```txt
Memory Used: 256 KB
Memory Free: 768 KB
```

---

## Process Command

```txt
> process
```

Displays simulated running processes.

Example:

```txt
PID   NAME
1     shell
2     taskA
3     taskB
```

---

# Key Learning Outcomes

Through this project, the developers learned:

- Basic operating system architecture
- Bootloader development
- Kernel initialization
- Hardware interaction
- Memory management concepts
- Process scheduling concepts
- Command-line implementation

---

# Challenges Encountered

Some challenges encountered during development include:

- Bootloader debugging
- Keyboard input handling
- Memory addressing
- Linking kernel binaries
- Emulator configuration

---

# Future Improvements

Possible future improvements:

- File system simulation
- Graphical user interface
- Real multitasking
- Dynamic memory allocation
- Mouse support
- Networking support
- File explorer
- User login system

---

# Researchers / Developers

| Name | Role |
|---|---|
| Your Name Here | Developer |
| Member 2 | Developer |
| Member 3 | Developer |

---

# Course Requirement

This project was developed as part of the Operating Systems Final Project requirement for:

**College of Information and Computer Studies**  
De La Salle University – Dasmariñas

---

# License

This project is intended for educational purposes only.

---

# Acknowledgements

Special thanks to:
- Operating Systems Professor
- DLSU-D College of Information and Computer Studies
- Open-source OS development communities
- QEMU and GRUB documentation contributors

---