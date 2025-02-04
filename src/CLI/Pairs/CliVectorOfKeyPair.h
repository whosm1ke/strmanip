#ifndef CLIVECTOROFKEYPAIR_H
#define CLIVECTOROFKEYPAIR_H
#include <string>
#include "CliPair.h"
#include "Enums/Key.h"
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>

class CliVectorOfKeyPair final : public CliPair<std::set<Key> > {
public:
    explicit CliVectorOfKeyPair(const std::string &arg) {
        CliVectorOfKeyPair::parse(arg);
    }

    void parse(const std::string &arg) override {
        const size_t pos = arg.find(" ");

        if (pos == std::string::npos) {
            throw std::invalid_argument(
                "Invalid argument format. Add space or provide value in format --name val1, val2...");
        }

        name = arg.substr(0, pos);
        const std::string values_str = arg.substr(pos + 1);

        std::stringstream ss(values_str);
        std::string token;

        while (std::getline(ss, token, ',')) {
            token = trim(token);
            value.insert(string_to_key(token));
        }
    }

private:
    static std::string trim(const std::string &str) {
        const size_t first = str.find_first_not_of(" \t");
        const size_t last = str.find_last_not_of(" \t");
        return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
    }
};

#endif
