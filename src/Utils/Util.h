#ifndef UTIL_H
#define UTIL_H
#include <Windows.h>
#include <string>
#include <filesystem>

class Util {
public:
    static std::string get_executable_path() {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path().string();
    }
};

#endif
