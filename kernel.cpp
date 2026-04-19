#include <iostream>
#include <string>
#include <map>
#include <emscripten.h>

class Kernel {
private:
    std::map<std::string, std::string> vfs; // Virtual File System
    std::string version = "1.0.0";

public:
    void boot() {
        std::cout << "[isaahi-os] Kernel " << version << " Booting..." << std::endl;
        vfs["/sys/os_name"] = "isaahi-os";
    }

    const char* read_file(std::string path) {
        if (vfs.count(path)) return vfs[path].c_str();
        return "ERR_404";
    }

    void write_file(std::string path, std::string content) {
        vfs[path] = content;
        std::cout << "[VFS] File Saved: " << path << " (" << content.length() << " bytes)" << std::endl;
    }
};

Kernel os;

extern "C" {
    // Standard Boot
    EMSCRIPTEN_KEEPALIVE
    void boot_kernel() { os.boot(); }

    // Read from VFS
    EMSCRIPTEN_KEEPALIVE
    const char* read_sys_file(const char* path) { 
        return os.read_file(path); 
    }

    // NEW: Write to VFS from JavaScript
    EMSCRIPTEN_KEEPALIVE
    void write_sys_file(const char* path, const char* content) {
        os.write_file(path, content);
    }
}
