# LasallianOS

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

### Command-Line Interface

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

---

## Project File Structure

```
DLSUDos/
├── index.html       ← Main page and GUI layout
├── style.css        ← All styling — terminal + desktop
├── kernel.js        ← Boot sequence and clock
├── shell.js         ← Command interpreter
├── processes.js     ← Process management simulation
├── memory.js        ← Memory management simulation
├── desktop.js       ← GUI desktop, windows, apps
├── dlsud.png        ← DLSUD logo (desktop watermark)
└── README.md        ← Documentation
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
