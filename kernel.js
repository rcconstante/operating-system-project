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
  document.getElementById("desktop").style.display = "block";
  
  initMemory(); 
  initProcesses(); 
  startClock();
}

function sleep(ms) { return new Promise(r => setTimeout(r, ms)); }

function startClock() {
  setInterval(() => {
    document.getElementById("clock").innerText = new Date().toLocaleTimeString();
  }, 1000);
}

window.onload = boot;