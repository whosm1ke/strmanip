#ifndef FILELOGGER_H
#define FILELOGGER_H
#include "Abstractions/I_Logger.h"
#include "Utils/Util.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

class FileLogger : public I_Logger {
public:
    void log(const std::string &message) override {
        const std::string path_to_log_file = Util::get_executable_path() + "\\" + "log.txt";

        auto now = std::chrono::system_clock::now();
        const std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::tm tm_struct{};
        localtime_s(&tm_struct, &now_time);

        std::ostringstream time_stream;
        time_stream << std::put_time(&tm_struct, "[%Y-%m-%d %H:%M:%S]");

        std::ofstream log_file(path_to_log_file, std::ios::app);
        if (!log_file) {
            throw std::runtime_error("Unable to open log file: " + path_to_log_file);
        }

        log_file << time_stream.str() << ": " << message << std::endl;
    }
};
#endif
