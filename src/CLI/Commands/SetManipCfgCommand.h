#ifndef SETMANIPCFGCOMMAND_H
#define SETMANIPCFGCOMMAND_H
#include <string>
#include <vector>
#include <iostream>
#include "CliCommand.h"
#include "Engine.h"

class SetManipCfgCommand final : public CliCommand {
public:
    SetManipCfgCommand() {
        setCallback([this]() {
            const auto strPair = dynamic_cast<CliStringPair *>(args[0].get());
            const std::string value = strPair->getValue();
            Engine::getInstance().set_current_manipulator_cfg(value);
        });
    }

    [[nodiscard]] bool supportsArguments() const override {
        return true;
    }

    [[nodiscard]] std::vector<CommandArgType> getSupportedArguments() const override {
        return {
            CommandArgType::MANIP_CFG
        };
    }
};
#endif
