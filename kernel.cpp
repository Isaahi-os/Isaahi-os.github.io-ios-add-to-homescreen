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
    }
};

Kernel os;

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void boot_kernel() { os.boot(); }

    EMSCRIPTEN_KEEPALIVE
    const char* get_version() { return "1.0.0"; }

    EMSCRIPTEN_KEEPALIVE
    const char* read_sys_file(const char* path) { return os.read_file(path); }
}
