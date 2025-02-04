#ifndef SETTRANDCFGCOMMAND_H
#define SETTRANDCFGCOMMAND_H
#include <vector>
#include <iostream>
#include "CliCommand.h"
#include "Engine.h"

class SetTransCfgCommand final : public CliCommand {
public:
    SetTransCfgCommand() {
        setCallback([this]() {
            const auto strPair = dynamic_cast<CliStringPair *>(args[0].get());
            const std::string value = strPair->getValue();
            Engine::getInstance().set_current_translator_cfg(value);
        });
    }

    [[nodiscard]] bool supportsArguments() const override {
        return true;
    }

    [[nodiscard]] std::vector<CommandArgType> getSupportedArguments() const override {
        return {
            CommandArgType::TRANSLATOR_CFG
        };
    }
};
#endif
