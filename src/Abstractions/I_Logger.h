#ifndef I_LOGGER_H
#define I_LOGGER_H
#include <string>

class I_Logger {
public:
    virtual ~I_Logger() = default;

    virtual void log(const std::string &msg) = 0;
};
#endif
