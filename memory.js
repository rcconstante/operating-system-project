const TOTAL_MEM = 1024;
let usedMem = 0;

function initMemory() {
  usedMem = 224; // kernel + shell + clock
}

function showMemory() {
  const free = TOTAL_MEM - usedMem;
  const pct  = Math.round((usedMem / TOTAL_MEM) * 100);
  const filled = Math.round(pct / 5);
  const bar = "#".repeat(filled) + ".".repeat(20 - filled);
  
  printOutput(
    "Memory Usage:<br>" +
    "&nbsp;&nbsp;Total : " + TOTAL_MEM + " KB<br>" +
    "&nbsp;&nbsp;Used&nbsp;&nbsp;: " + usedMem   + " KB<br>" +
    "&nbsp;&nbsp;Free&nbsp;&nbsp;: " + free      + " KB<br>" +
    "&nbsp;&nbsp;[" + bar + "] " + pct + "%"
  );
}