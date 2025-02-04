#ifndef RUNCOMMAND_H
#define RUNCOMMAND_H
#include "CliCommand.h"
#include "Engine.h"

class RunCommand final : public CliCommand {
public:
    RunCommand() {
        setCallback([this]() {
            Engine::getInstance().run();
        });
    }

    [[nodiscard]] bool supportsArguments() const override {
        return false;
    }
};
#endif
