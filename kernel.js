// kernel.js - Pure JS Edition
const Kernel = {
    vfs: {},
    version: "1.0.1-js",

    boot: function() {
        console.log(`[isaahi-os] Kernel ${this.version} Booting...`);
        
        // 1. Pre-install Isaahi-browser [cite: 1]
        this.write_file("/apps/Isaahi-browser/index.html", `
            <div style="background:#eee; padding:5px; display:flex; gap:5px;">
                <input type='text' id='addr' style='flex:1' value='https://www.bing.com'>
                <button onclick="document.getElementById('vw').src=document.getElementById('addr').value">Go</button>
            </div>
            <iframe id="vw" src="https://www.bing.com" style="width:100%; height:calc(100% - 40px); border:none;"></iframe>
        `);
        this.write_file("/apps/Isaahi-browser/style.css", "body { margin:0; font-family:sans-serif; }");

        // 2. Pre-install my_app [cite: 2]
        this.write_file("/apps/my_app/index.html", `
            <div style="padding:20px; text-align:center;">
                <h1>My App</h1>
                <p>Welcome to your custom application!</p>
            </div>
        `);
        this.write_file("/apps/my_app/style.css", "body { background: white; color: black; }");
    },

    read_file: function(path) {
        return this.vfs[path] || "ERR_404";
    },

    write_file: function(path, content) {
        this.vfs[path] = content;
    }
};

// Interface for index.html
var Module = {
    onRuntimeInitialized: function() {
        Kernel.boot();
        if (window.onKernelLoad) window.onKernelLoad();
    },
    ccall: function(func, ret, types, args) {
        if (func === 'write_sys_file') return Kernel.write_file(args[0], args[1]);
        if (func === 'read_sys_file') return Kernel.read_file(args[0]);
    }
};

// Self-start
setTimeout(() => Module.onRuntimeInitialized(), 100);
