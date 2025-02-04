#ifndef CLIBOOLPAIR_H
#define CLIBOOLPAIR_H
#include <string>
#include "CliPair.h"
#include <stdexcept>

class CliBoolPair final : public CliPair<bool> {
public:
    explicit CliBoolPair(const std::string &arg) {
        CliBoolPair::parse(arg);
    }

    void parse(const std::string &arg) override {
        const size_t pos = arg.find(" ");

        if (pos == std::string::npos) {
            throw std::invalid_argument("Boolean argument must contain a value (T or F). Invalid input: " + arg);
        }

        name = arg.substr(0, pos);

        if (const std::string bool_value = arg.substr(pos + 1); bool_value == "T" || bool_value == "t") {
            value = true;
        } else if (bool_value == "F" || bool_value == "f") {
            value = false;
        } else {
            throw std::invalid_argument("Invalid boolean value: " + bool_value);
        }
    }
};
#endif
