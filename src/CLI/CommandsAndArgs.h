#ifndef COMMANDANDARGS_H
#define COMMANDANDARGS_H
#include "Pairs/CliLanguagePair.h"
#include "Pairs/CliStringPair.h"
#include "Pairs/CliBoolPair.h"
#include "Pairs/CliVectorOfKeyPair.h"
#include "Commands/CliCommand.h"
#include "Commands/RunCommand.h"
#include "Commands/ConfigureCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/SetManipCfgCommand.h"
#include "Commands/SetTransCfgCommand.h"
#include "Commands/ListKeysCommand.h"
#include "Commands/ListLanguagesCommand.h"
#include "Commands/ListBindingsCommand.h"
#include "Enums/CommandType.h"
#include "Enums/CommandArgType.h"
#include <memory>
#include <functional>

class CommandsAndArgs {
public:
    static std::map<CommandArgType, std::function<std::unique_ptr<CliPairBase>(const std::string &)> > argsMap;
    static std::map<CommandType, std::function<std::unique_ptr<CliCommand>()> > commandsMap;
};

static std::map<CommandArgType, std::function<std::unique_ptr<CliPairBase>(const std::string &)> > argsMap = {
    {
        CommandArgType::MANIP_CFG, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliStringPair>(arg);
        }
    },
    {
        CommandArgType::TRANSLATOR_CFG, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliStringPair>(arg);
        }
    },
    {
        CommandArgType::ON_WINDOWS_START, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliBoolPair>(arg);
        }
    },
    {
        CommandArgType::STOP_PROGRAM_KEY_BINDING, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliVectorOfKeyPair>(arg);
        }
    },
    {
        CommandArgType::CAPITALIZE_KEY_BINDING, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliVectorOfKeyPair>(arg);
        }
    },
    {
        CommandArgType::TRANSLIT_KEYS_KEY_BINDING, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliVectorOfKeyPair>(arg);
        }
    },
    {
        CommandArgType::LOWER_KEYS_KEY_BINDING, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliVectorOfKeyPair>(arg);
        }
    },
    {
        CommandArgType::UPPER_KEYS_KEY_BINDING, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliVectorOfKeyPair>(arg);
        }
    },
    {
        CommandArgType::DEEPL_API_KEY, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliStringPair>(arg);
        }
    },
    {
        CommandArgType::TARGET_LANGUAGE, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliLanguagePair>(arg);
        }
    },
    {
        CommandArgType::SOURCE_LANGUAGE, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliLanguagePair>(arg);
        }
    },
    {
        CommandArgType::SWAP_LANG_KEY_BINDING, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliVectorOfKeyPair>(arg);
        }
    },
    {
        CommandArgType::TRANSLATE_KEY_BINDING, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliVectorOfKeyPair>(arg);
        }
    },
    {
        CommandArgType::ENABLE_BIND_SUBSETS, [](const std::string &arg) -> std::unique_ptr<CliPairBase> {
            return std::make_unique<CliBoolPair>(arg);
        }
    }
};

static std::map<CommandType, std::function<std::unique_ptr<CliCommand>()> > commandsMap = {
    {
        CommandType::RUN, []() -> std::unique_ptr<CliCommand> {
            return std::make_unique<RunCommand>();
        }
    },
    {
        CommandType::CONFIGURE, []() -> std::unique_ptr<CliCommand> {
            return std::make_unique<ConfigureCommand>();
        }
    },
    {
        CommandType::HELP, []() -> std::unique_ptr<CliCommand> {
            return std::make_unique<HelpCommand>();
        }
    },
    {
        CommandType::SET_MANIP_CFG, []() -> std::unique_ptr<CliCommand> {
            return std::make_unique<SetManipCfgCommand>();
        }
    },
    {
        CommandType::SET_TRAN_CFG, []() -> std::unique_ptr<CliCommand> {
            return std::make_unique<SetTransCfgCommand>();
        }
    },
    {
        CommandType::LIST_KEYS, []() -> std::unique_ptr<CliCommand> {
            return std::make_unique<ListKeysCommand>();
        }
    },
    {
        CommandType::LIST_LANGUAGES, []() -> std::unique_ptr<CliCommand> {
            return std::make_unique<ListLanguagesCommand>();
        }
    },
    {
        CommandType::LIST_BINDS, []() -> std::unique_ptr<CliCommand> {
            return std::make_unique<ListBindingsCommand>();
        }
    }
};


#endif
