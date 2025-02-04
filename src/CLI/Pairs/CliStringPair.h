

#ifndef CLISTRINGPAIR_H
#define CLISTRINGPAIR_H
#include <string>
#include "CliPair.h"
#include <stdexcept>

class CliStringPair final : public CliPair<std::string> {
public:
    explicit CliStringPair(const std::string &arg) {
        CliStringPair::parse(arg);
    }

    void parse(const std::string &arg) override {
        size_t pos = arg.find(" ");

        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid argument format. Add space or provide value in format --name value");
        }
        name = arg.substr(0, pos);
        value = arg.substr(pos + 1);
    }
};
#endif
