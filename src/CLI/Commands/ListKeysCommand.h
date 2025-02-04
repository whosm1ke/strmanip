#ifndef LISTKEYSCOMMAND_H
#define LISTKEYSCOMMAND_H
#include "InteraptableCliCommand.h"
#include "Engine.h"

class ListKeysCommand final : public InteraptableCliCommand {
public:
    ListKeysCommand() {
        setCallback([this]() {
            Engine::getInstance().display_keys();
        });
    }

    [[nodiscard]] bool supportsArguments() const override {
        return false;
    }
};
#endif
