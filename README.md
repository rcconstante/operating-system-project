# DLSUDos

**DE LA SALLE UNIVERSITY – DASMARIÑAS (DLSU-D)**  
College of Information and Computer Studies  
Operating Systems — Final Project

---

DLSUDos is a browser-based operating system simulation built entirely in HTML, CSS, and JavaScript — no installation required. It covers all rubric requirements including a boot sequence, kernel simulation, command-line interface, process management, and memory management. Type `boot os` in the terminal to launch a full Windows-style GUI desktop with draggable icons, resizable windows, a Tic-Tac-Toe game, and a background color picker.

---

## Project Information

| Category        | Details                             |
| --------------- | ----------------------------------- |
| Project Name    | DLSUDos                             |
| Course          | Operating Systems                   |
| School          | De La Salle University – Dasmariñas |
| Language        | HTML, CSS, JavaScript               |
| Platform        | Browser — no installation needed    |
| Hosting         | GitHub Pages                        |
| Version Control | GitHub — one branch per member      |

---

## Features

### Booting Mechanism _(15 pts)_

- Animated boot screen with sequential `[OK]` initialization messages.
- Simulates kernel load, memory init, process manager start, and shell launch.
- Transitions to the terminal desktop after boot completes.

### Kernel Implementation _(20 pts)_

- `kernel.js` handles the full boot sequence and subsystem initialization.
- Calls `initMemory()`, `initProcesses()`, and `startClock()` on load.
- Live clock displayed in the terminal taskbar.

### Command-Line Interface _(15 pts)_

| Command       | Description                                |
| ------------- | ------------------------------------------ |
| `help`        | Displays all available commands            |
| `clear`       | Clears the terminal output                 |
| `ps`          | Lists all simulated running processes      |
| `kill <pid>`  | Terminates a simulated process by PID      |
| `mem`         | Displays memory usage with a visual bar    |
| `date`        | Prints the current date and time           |
| `echo <text>` | Prints text to the terminal                |
| `boot os`     | Launches the GUI desktop _(bonus feature)_ |
| `exit`        | Shuts down and reloads the OS              |

### Process Management Simulation _(15 pts)_

- Fixed process table with PID, name, status, and memory usage.
- `ps` displays a formatted table of all running processes.
- `kill <pid>` removes a user process from the table.
- System processes (kernel, shell) are protected and cannot be killed.

### Memory Management Simulation _(10 pts)_

- Fixed 1024 KB simulated memory model.
- `mem` displays total, used, and free memory in KB.
- ASCII progress bar showing memory usage percentage.

### Advanced Features _(10 pts)_

- Live clock in the taskbar updating every second.
- `kill` command with PID validation and error handling.
- `echo` command for terminal text output.
- `boot os` command launching a full GUI desktop environment.

---

## Project File Structure

```
DLSUDos/
├── index.html       ← Main page and GUI layout          (Member 1 & 5)
├── style.css        ← All styling — terminal + desktop  (Member 5)
├── kernel.js        ← Boot sequence and clock           (Member 1)
├── shell.js         ← Command interpreter               (Member 2)
├── processes.js     ← Process management simulation     (Member 3)
├── memory.js        ← Memory management simulation      (Member 4)
├── desktop.js       ← GUI desktop, windows, apps        (Member 5)
├── dlsud.png        ← DLSUD logo (desktop watermark)
└── README.md        ← Documentation                     (Member 5)
```

---

## How to Run

No build tools or installations required.

1. Clone or download this repository.
2. Open `index.html` in any modern browser (Chrome or Firefox recommended).
3. Watch the boot sequence complete.
4. Type commands in the terminal, or type `boot os` to launch the GUI desktop.

**Live on GitHub Pages:** `https://yourusername.github.io/dlsudos`

---

## System Architecture

```
+-------------------+
|   Boot Sequence   |
|   (kernel.js)     |
+-------------------+
          |
          v
+-------------------+
|  Terminal Shell   |
|   (shell.js)      |
+-------------------+
     |         |
     v         v
+--------+ +--------+
|Process | |Memory  |
|Manager | |Manager |
+--------+ +--------+
          |
       boot os
          |
          v
+-------------------+
|   GUI Desktop     |
|   (desktop.js)    |
+-------------------+
          |
          v
+-------------------+
| Windows / Apps /  |
| Tic-Tac-Toe       |
+-------------------+
```

---

## Demo Commands

```
help
ps
kill 3
mem
date
echo Hello, DLSUDos!
boot os
clear
exit
```

---

## Limitations

This is an educational prototype. It does not include real multitasking, actual memory allocation, a file system, persistent storage, or true hardware interaction. All process and memory data is simulated in-memory at runtime and resets on page reload.

---

## License

This project is intended for educational use at De La Salle University – Dasmariñas.
