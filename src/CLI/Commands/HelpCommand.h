#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H
#include "InteraptableCliCommand.h"
#include "Engine.h"

class HelpCommand final : public InteraptableCliCommand {
public:
    HelpCommand() {
        setCallback([this]() {
            Engine::getInstance().display_help_message();
        });
    }

    [[nodiscard]] bool supportsArguments() const override {
        return false;
    }
};
#endif
