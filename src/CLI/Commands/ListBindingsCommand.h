#ifndef LISTBINDINGSCOMMAND_H
#define LISTBINDINGSCOMMAND_H
#include "InteraptableCliCommand.h"
#include "Engine.h"

class ListBindingsCommand final : public InteraptableCliCommand {
public:
    ListBindingsCommand() {
        setCallback([this]() {
            Engine::getInstance().list_bindings();
        });
    }

    [[nodiscard]] bool supportsArguments() const override {
        return false;
    }
};
#endif
