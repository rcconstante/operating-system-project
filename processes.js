let processes = [];

function initProcesses() {
  processes = [
    { pid: 1, name: "kernel",  status: "running",  memory: 128 },
    { pid: 2, name: "shell",   status: "running",  memory: 64  },
    { pid: 3, name: "clock",   status: "sleeping", memory: 32  },
  ];
}

function showProcesses() {
  let table = "PID&nbsp;&nbsp;&nbsp;NAME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;STATUS&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;MEM<br>";
  table += "─".repeat(44) + "<br>";

  processes.forEach(p => {
    table += p.pid + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" +
             p.name.padEnd(14, " ") +
             p.status.padEnd(11, " ") +
             p.memory + "KB<br>";
  });

  if (typeof GUI !== "undefined") {
    Object.entries(GUI.windowPids).forEach(([pid, winId]) => {
      const win = GUI.windows[winId];
      if (!win) return;
      const name = win.title.toLowerCase().replace(/\s+/g, "-").padEnd(14, " ");
      table += pid + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + name + "running&nbsp;&nbsp;&nbsp;&nbsp;" + "--<br>";
    });
  }

  printOutput(table);
}

function killProcess(pid) {
  if (typeof GUI !== "undefined" && GUI.windowPids[pid]) {
    const winId = GUI.windowPids[pid];
    const name = GUI.windows[winId] ? GUI.windows[winId].title : "app";
    GUI.closeWindow(winId);
    printOutput("Killed: " + name + " (PID " + pid + ")");
    return;
  }
  if (pid === 1 || pid === 2) {
    printOutput("Cannot kill system process.");
    return;
  }
  const idx = processes.findIndex(p => p.pid === pid);
  if (idx === -1) {
    printOutput("No process with PID " + pid);
  } else {
    printOutput("Killed: " + processes[idx].name + " (PID " + pid + ")");
    processes.splice(idx, 1);
  }
}
