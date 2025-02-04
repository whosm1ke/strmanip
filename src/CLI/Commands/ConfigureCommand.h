#ifndef CONFIGURECOMMAND_H
#define CONFIGURECOMMAND_H
#include <vector>
#include "CliCommand.h"

class ConfigureCommand final : public CliCommand {
public:
    ConfigureCommand() {
        setCallback([this]() {
            Engine::getInstance().configure_engine(args);
        });
    }

    [[nodiscard]] bool supportsArguments() const override {
        return true;
    }

    [[nodiscard]] std::vector<CommandArgType> getSupportedArguments() const override {
        return {
            CommandArgType::TRANSLIT_KEYS_KEY_BINDING, CommandArgType::STOP_PROGRAM_KEY_BINDING,
            CommandArgType::CAPITALIZE_KEY_BINDING, CommandArgType::UPPER_KEYS_KEY_BINDING,
            CommandArgType::TRANSLATE_KEY_BINDING, CommandArgType::LOWER_KEYS_KEY_BINDING,
            CommandArgType::SWAP_LANG_KEY_BINDING, CommandArgType::TARGET_LANGUAGE, CommandArgType::SOURCE_LANGUAGE,
            CommandArgType::ON_WINDOWS_START, CommandArgType::DEEPL_API_KEY, CommandArgType::ENABLE_BIND_SUBSETS
        };
    }
};
#endif
