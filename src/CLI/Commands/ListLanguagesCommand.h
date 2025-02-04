#ifndef LISTLANGUAGESCOMMAND_H
#define LISTLANGUAGESCOMMAND_H
#include "InteraptableCliCommand.h"
#include "Engine.h"

class ListLanguagesCommand final : public InteraptableCliCommand {
public:
    ListLanguagesCommand() {
        setCallback([this]() {
            Engine::getInstance().display_languages();
        });
    }

    [[nodiscard]] bool supportsArguments() const override {
        return false;
    }
};
#endif
