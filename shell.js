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
      printOutput("Available commands: help, clear, ps, kill &lt;name|pid&gt;, mem, date, echo &lt;text&gt;, boot os, exit");
      break;
    case "clear": document.getElementById("output").innerHTML = ""; break;
    case "ps":    showProcesses(); break;
    case "kill": {
      var killArg = parts.slice(1).join(" ");
      if (!killArg) { printOutput("Usage: kill &lt;app-name&gt; or kill &lt;pid&gt;"); break; }
      if (!isNaN(killArg) && parts.length === 2) {
        killProcess(parseInt(killArg));
      } else {
        var killName = killArg.replace(/-/g, " ");
        if (typeof GUI !== "undefined" && GUI.killByName(killName)) {
          printOutput("Closed: " + killName);
        } else {
          printOutput("No app found: " + killArg + ". Use ps to list processes.");
        }
      }
      break;
    }
    case "mem":   showMemory(); break;
    case "date":  printOutput(new Date().toString()); break;
    case "echo":  printOutput(parts.slice(1).join(" ")); break;
    case "boot":
      if (parts[1] === "os") {
        printOutput("[OK] Launching GUI desktop...");
        setTimeout(() => {
          document.getElementById('desktop').style.display = 'none';
          GUI.boot();
        }, 600);
      } else {
        printOutput("Usage: boot os");
      }
      break;
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
  out.scrollTop = out.scrollHeight;
}
