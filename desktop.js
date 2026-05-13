const GUI = {
  windows: {}, nextId: 1, topZ: 100, startTime: Date.now(),

  boot() {
    document.getElementById('gui-desktop').style.display = 'flex';
    this.placeIcons();
    this.startClock();
    this.bindEvents();
  },

  placeIcons() {
    const icons = [
      { label: 'My Computer', icon: '🖥️', type: 'computer'  },
      { label: 'Documents',   icon: '📁', type: 'documents' },
      { label: 'Notepad',     icon: '📝', type: 'notepad'   },
      { label: 'Tic-Tac-Toe',icon: '⭕',  type: 'ttt'       },
      { label: 'Recycle Bin', icon: '🗑️', type: 'recycle'   },
    ];
    const area = document.getElementById('gui-desktop-area');
    icons.forEach((ic, i) => {
      const el = document.createElement('div');
      el.className = 'desktop-icon';
      el.style.left = '16px';
      el.style.top  = (16 + i * 88) + 'px';
      el.innerHTML  = `<div class="icon-img">${ic.icon}</div><div class="icon-label">${ic.label}</div>`;

      let clicks = 0;
      el.addEventListener('click', e => {
        e.stopPropagation();
        document.querySelectorAll('.desktop-icon').forEach(d => d.classList.remove('selected'));
        el.classList.add('selected');
        if (++clicks === 2) { this.openApp(ic.type); clicks = 0; }
        setTimeout(() => { clicks = 0; }, 400);
      });
      this.makeIconDraggable(el, area);
      area.appendChild(el);
    });

    area.addEventListener('click', () =>
      document.querySelectorAll('.desktop-icon').forEach(d => d.classList.remove('selected')));
  },

  makeIconDraggable(el, area) {
    let dx, dy, dragging = false;
    el.addEventListener('mousedown', e => {
      dragging = true;
      dx = e.clientX - el.offsetLeft;
      dy = e.clientY - el.offsetTop;
      el.style.zIndex = 80;
      el.style.opacity = '0.8';
      e.stopPropagation();
    });
    document.addEventListener('mousemove', e => {
      if (!dragging) return;
      el.style.left = Math.max(0, Math.min(area.clientWidth  - el.offsetWidth,  e.clientX - dx)) + 'px';
      el.style.top  = Math.max(0, Math.min(area.clientHeight - el.offsetHeight, e.clientY - dy)) + 'px';
    });
    document.addEventListener('mouseup', () => {
      if (!dragging) return;
      dragging = false;
      el.style.zIndex = '';
      el.style.opacity = '1';
    });
  },

  startClock() {
    const tick = () => {
      const now = new Date();
      document.getElementById('gui-clock').textContent =
        now.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
      const up = document.getElementById('gui-uptime');
      if (up) {
        const s = Math.floor((Date.now() - this.startTime) / 1000);
        up.textContent = s < 60 ? s + 's' : Math.floor(s / 60) + 'm ' + (s % 60) + 's';
      }
    };
    tick(); setInterval(tick, 1000);
  },

  bindEvents() {
    const ctx = document.getElementById('context-menu');

    document.getElementById('gui-desktop-area').addEventListener('contextmenu', e => {
      e.preventDefault();
      ctx.style.cssText = `display:block;left:${e.clientX}px;top:${e.clientY}px`;
    });

    document.addEventListener('click', () => {
      ctx.style.display = 'none';
      document.getElementById('start-menu').style.display = 'none';
      document.getElementById('color-picker').style.display = 'none';
    });

    document.getElementById('start-btn').addEventListener('click', e => {
      e.stopPropagation();
      const sm = document.getElementById('start-menu');
      sm.style.display = sm.style.display === 'block' ? 'none' : 'block';
    });

    document.getElementById('color-btn').addEventListener('click', e => {
      e.stopPropagation();
      const cp = document.getElementById('color-picker');
      cp.style.display = cp.style.display === 'flex' ? 'none' : 'flex';
    });
  },

  setBg(color) {
    document.getElementById('gui-desktop').style.background = color;
    document.getElementById('color-picker').style.display = 'none';
  },

  openApp(type) {
    document.getElementById('start-menu').style.display = 'none';
    const map = {
      computer:  ['My Computer', '🖥️', this.computerContent(), { w: 440, h: 300 }],
      documents: ['Documents',   '📁', this.docsContent(),     { w: 460, h: 320 }],
      recycle:   ['Recycle Bin', '🗑️', this.recycleContent(),  { w: 380, h: 240 }],
      notepad:   ['Notepad',     '📝', this.notepadContent(),  { w: 460, h: 340 }],
      ttt:       ['Tic-Tac-Toe', '⭕', this.tttContent(),      { w: 280, h: 340 }],
    };
    const args = map[type];
    if (args) this.createWindow(...args);
  },

  createWindow(title, icon, content, opts = {}) {
    const id  = 'win-' + this.nextId++;
    const w   = opts.w || 440;
    const h   = opts.h || 300;
    const area = document.getElementById('gui-desktop-area');
    const off = ((this.nextId - 2) % 6) * 22;
    const x   = Math.min(120 + off, area.clientWidth  - w - 20);
    const y   = Math.min(20  + off, area.clientHeight - h - 20);

    const win = document.createElement('div');
    win.className = 'gui-window';
    win.id = id;
    win.style.cssText = `left:${x}px;top:${y}px;width:${w}px;height:${h}px;z-index:${++this.topZ}`;
    win.innerHTML = `
      <div class="window-titlebar">
        <span class="wtitle">${icon} ${title}</span>
        <div class="window-controls">
          <button class="win-btn wmin">_</button>
          <button class="win-btn wmax">□</button>
          <button class="win-btn wclose">✕</button>
        </div>
      </div>
      <div class="window-body">${content}</div>`;

    area.appendChild(win);
    this.windows[id] = { title, icon };
    this.makeDraggable(win);
    this.makeResizable(win);
    win.querySelector('.wclose').onclick = () => this.closeWindow(id);
    win.querySelector('.wmin').onclick   = () => this.hideWindow(id);
    win.querySelector('.wmax').onclick   = () => win.classList.toggle('maximized');
    win.addEventListener('mousedown',    () => this.focusWindow(id));
    this.addTaskbarBtn(id, icon, title);
    this.focusWindow(id);
  },

  focusWindow(id) {
    const win = document.getElementById(id);
    if (win) win.style.zIndex = ++this.topZ;
    document.querySelectorAll('.taskbar-btn').forEach(b => b.classList.remove('active'));
    document.querySelector(`.taskbar-btn[data-id="${id}"]`)?.classList.add('active');
  },

  closeWindow(id) {
    document.getElementById(id)?.remove();
    delete this.windows[id];
    document.querySelector(`.taskbar-btn[data-id="${id}"]`)?.remove();
  },

  hideWindow(id) {
    const win = document.getElementById(id);
    if (win) win.style.display = 'none';
    document.querySelector(`.taskbar-btn[data-id="${id}"]`)?.classList.remove('active');
  },

  addTaskbarBtn(id, icon, title) {
    const btn = document.createElement('button');
    btn.className   = 'taskbar-btn active';
    btn.dataset.id  = id;
    btn.textContent = icon + ' ' + title;
    btn.onclick = () => {
      const win = document.getElementById(id);
      if (!win) return;
      if (win.style.display === 'none') { win.style.display = 'flex'; this.focusWindow(id); }
      else this.hideWindow(id);
    };
    document.getElementById('taskbar-windows').appendChild(btn);
  },

  makeDraggable(win) {
    const bar = win.querySelector('.window-titlebar');
    let dx, dy, on = false;
    bar.addEventListener('mousedown', e => {
      if (e.target.classList.contains('win-btn')) return;
      win.classList.remove('maximized');
      on = true; dx = e.clientX - win.offsetLeft; dy = e.clientY - win.offsetTop;
      e.preventDefault();
    });
    document.addEventListener('mousemove', e => {
      if (!on) return;
      const a = document.getElementById('gui-desktop-area');
      win.style.left = Math.max(0, Math.min(a.clientWidth  - win.offsetWidth,  e.clientX - dx)) + 'px';
      win.style.top  = Math.max(0, Math.min(a.clientHeight - win.offsetHeight, e.clientY - dy)) + 'px';
    });
    document.addEventListener('mouseup', () => { on = false; });
  },

  makeResizable(win) {
    const h = document.createElement('div');
    h.className = 'resize-handle';
    win.appendChild(h);
    let on = false, sx, sy, sw, sh;
    h.addEventListener('mousedown', e => {
      on = true; sx = e.clientX; sy = e.clientY; sw = win.offsetWidth; sh = win.offsetHeight;
      e.preventDefault(); e.stopPropagation();
    });
    document.addEventListener('mousemove', e => {
      if (!on) return;
      win.style.width  = Math.max(240, sw + e.clientX - sx) + 'px';
      win.style.height = Math.max(160, sh + e.clientY - sy) + 'px';
    });
    document.addEventListener('mouseup', () => { on = false; });
  },

  // ── App content ──────────────────────────────────────────────────────

  computerContent: () => `
    <div class="exp-bar"><input class="exp-addr" value="My Computer" readonly></div>
    <div class="file-grid">
      <div class="file-item" ondblclick="GUI.openApp('documents')"><div class="fi">💾</div><div>Local Disk (C:)</div></div>
      <div class="file-item"><div class="fi">💿</div><div>CD Drive (D:)</div></div>
      <div class="file-item"><div class="fi">🖨️</div><div>Printers</div></div>
      <div class="file-item"><div class="fi">🌐</div><div>Network</div></div>
    </div>`,

  docsContent: () => `
    <div class="exp-bar"><input class="exp-addr" value="C:\\Documents" readonly></div>
    <div class="file-grid">
      <div class="file-item"><div class="fi">📁</div><div>Pictures</div></div>
      <div class="file-item"><div class="fi">📁</div><div>Music</div></div>
      <div class="file-item"><div class="fi">📁</div><div>Downloads</div></div>
      <div class="file-item"><div class="fi">📄</div><div>readme.txt</div></div>
      <div class="file-item"><div class="fi">🖼️</div><div>photo.png</div></div>
      <div class="file-item"><div class="fi">🎵</div><div>song.mp3</div></div>
    </div>`,

  recycleContent: () => `
    <div style="text-align:center;padding:40px;color:#999">
      <div style="font-size:52px">🗑️</div>
      <div style="margin-top:10px;font-size:13px">Recycle Bin is empty</div>
    </div>`,

  notepadContent: () => `
    <div style="display:flex;flex-direction:column;height:100%">
      <div class="np-bar"><span>File</span><span>Edit</span><span>Format</span></div>
      <textarea class="np-ta" placeholder="Start typing..."></textarea>
    </div>`,

  tttContent() {
    const gid = 'ttt' + Date.now();
    setTimeout(() => this.initTTT(gid), 0);
    return `
      <div class="ttt-wrap" id="${gid}">
        <div class="ttt-status" id="${gid}-s">X's turn</div>
        <div class="ttt-board" id="${gid}-b"></div>
        <button class="ttt-reset" onclick="GUI.resetTTT('${gid}')">New Game</button>
      </div>`;
  },

  initTTT(gid) {
    window['_ttt' + gid] = { board: Array(9).fill(''), cur: 'X', over: false };
    const boardEl = document.getElementById(gid + '-b');
    if (!boardEl) return;
    boardEl.innerHTML = '';
    for (let i = 0; i < 9; i++) {
      const c = document.createElement('button');
      c.className = 'ttt-cell';
      c.onclick = () => this.tttMove(gid, i);
      boardEl.appendChild(c);
    }
    document.getElementById(gid + '-s').textContent = "X's turn";
  },

  resetTTT(gid) { this.initTTT(gid); },

  tttMove(gid, i) {
    const st = window['_ttt' + gid];
    if (!st || st.over || st.board[i]) return;
    st.board[i] = st.cur;
    const cells = document.querySelectorAll('#' + gid + '-b .ttt-cell');
    cells[i].textContent = st.cur;
    cells[i].dataset.p = st.cur;

    const lines = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]];
    const win = lines.find(([a,b,c]) =>
      st.board[a] && st.board[a] === st.board[b] && st.board[b] === st.board[c]);
    const status = document.getElementById(gid + '-s');

    if (win) {
      win.forEach(j => cells[j].classList.add('ttt-win'));
      status.textContent = st.cur + ' wins! 🎉';
      st.over = true;
    } else if (st.board.every(Boolean)) {
      status.textContent = "Draw! 🤝";
      st.over = true;
    } else {
      st.cur = st.cur === 'X' ? 'O' : 'X';
      status.textContent = st.cur + "'s turn";
    }
  },
};
