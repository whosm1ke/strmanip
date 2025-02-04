#ifndef CLIPAIR_H
#define CLIPAIR_H
#include <string>
#include "CliPairBase.h"
#include <sstream>

template<typename T>
class CliPair : public CliPairBase {
public:
    CliPair() = default;

    ~CliPair() override = default;

    void parse(const std::string &arg) override = 0;

    const CommandArgType getCommandArgType() const override { return string_to_arg(name); }
    const std::string &getArgName() const override { return name; }

    T getValue() const {
        return value;
    }

protected:
    std::string name;
    T value;
};
#endif
