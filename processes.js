let processes = [];

function initProcesses() {
  processes = [
    { pid: 1, name: "kernel",  status: "running",  memory: 128 },
    { pid: 2, name: "shell",   status: "running",  memory: 64  },
    { pid: 3, name: "clock",   status: "sleeping", memory: 32  },
  ];
}

function showProcesses() {
  let table = "PID   NAME        STATUS      MEM<br>";
  processes.forEach(p => {
    table += p.pid + "     " + p.name.padEnd(10, "&nbsp;") + " " +
             p.status.padEnd(10, "&nbsp;") + " " + p.memory + "KB<br>";
  });
  printOutput(table);
}

function killProcess(pid) {
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