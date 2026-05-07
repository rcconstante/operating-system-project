document.getElementById("cmd-input")
  .addEventListener("keydown", function(e) {
    if (e.key === "Enter") {
      const input = this.value.trim();
      printOutput("DLSUDos> " + input);
      if (input !== "") handleCommand(input);
      this.value = "";
    }
});

function handleCommand(cmd) {
  const parts = cmd.split(" ");
  switch(parts[0]) {
    case "help":  
      printOutput("Available commands: help, clear, ps, kill &lt;pid&gt;, mem, date, echo &lt;text&gt;, exit"); 
      break;
    case "clear": document.getElementById("output").innerHTML = ""; break;
    case "ps":    showProcesses(); break;
    case "kill":  killProcess(parseInt(parts[1])); break;
    case "mem":   showMemory(); break;
    case "date":  printOutput(new Date().toString()); break;
    case "echo":  printOutput(parts.slice(1).join(" ")); break;
    case "exit":
      printOutput("Shutting down... Goodbye!");
      setTimeout(() => location.reload(), 1500); break;
    default:
      printOutput("Command not found: " + cmd + ". Type help.");
  }
}

function printOutput(text) {
  const out = document.getElementById("output");
  out.innerHTML += "<div>" + text + "</div>";
  out.scrollTop = out.scrollHeight; // Auto-scroll to bottom
}