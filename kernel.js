const bootMessages = [
  "[OK] Loading kernel...",
  "[OK] Initializing memory...",
  "[OK] Starting process manager...",
  "[OK] Launching shell...",
  "[OK] Done! Welcome to DLSUDos v1.0"
];

async function boot() {
  const bootText = document.getElementById("boot-text");
  for (let msg of bootMessages) {
    bootText.innerHTML += msg + "<br>";
    await sleep(600);
  }
  await sleep(800);
  document.getElementById("boot-screen").style.display = "none";
  document.getElementById("desktop").style.display = "flex";

  initMemory();
  initProcesses();
  startClock();
  showWelcome();
}

function sleep(ms) { return new Promise(r => setTimeout(r, ms)); }

function showWelcome() {
  const banner = [
    ' __    __     _                          ',
    '/ / /\\ \\ \\___| | ___ ___  _ __ ___   ___ ',
    '\\ \\/  \\/ / _ \\ |/ __/ _ \\| \'_ ` _ \\ / _ \\',
    ' \\  /\\  /  __/ | (_| (_) | | | | | |  __/',
    '  \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|',
    '',
    'De La Salle University - Dasmariñas',
    'Operating Systems Final Project — DLSUDos v1.0',
    '─'.repeat(52),
    '',
    'Available commands:',
    '  help         Show this command list',
    '  ps           List running processes',
    '  kill &lt;pid&gt;   Terminate a process by PID',
    '  mem          Show memory usage',
    '  date         Print current date and time',
    '  echo &lt;text&gt;  Print text to terminal',
    '  boot os      Launch the GUI desktop',
    '  clear        Clear the terminal',
    '  exit         Shut down DLSUDos',
    '',
    '─'.repeat(52),
  ];
  const out = document.getElementById("output");
  out.innerHTML += `<pre style="color:#00ff00;line-height:1.4;">${banner.join('\n')}</pre>`;
}

function startClock() {
  setInterval(() => {
    document.getElementById("clock").innerText = new Date().toLocaleTimeString();
  }, 1000);
}

window.onload = boot;