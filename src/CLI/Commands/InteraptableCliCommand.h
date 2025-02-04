#ifndef INTERAPTABLECLICOMMAND_H
#define INTERAPTABLECLICOMMAND_H
#include "CliCommand.h"

class InteraptableCliCommand : public CliCommand {
public:
    ~InteraptableCliCommand() override = default;

    [[nodiscard]] bool supportsArguments() const override = 0;
};

#endif
