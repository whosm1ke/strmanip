#ifndef CLIPAIRBASE_H
#define CLIPAIRBASE_H
#include <string>
#include <Enums/CommandArgType.h>

class CliPairBase {
public:
    virtual ~CliPairBase() = default;

    virtual void parse(const std::string &arg) = 0;

    virtual const CommandArgType getCommandArgType() const = 0;

    virtual const std::string &getArgName() const = 0;
};
#endif
