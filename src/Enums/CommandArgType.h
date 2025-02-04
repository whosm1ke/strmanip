#ifndef COMMANDARGTYPE_H
#define COMMANDARGTYPE_H
#include <string>
#include <map>

enum class CommandArgType {
    MANIP_CFG = 0,
    TRANSLATOR_CFG = 1,
    ON_WINDOWS_START = 2,
    STOP_PROGRAM_KEY_BINDING = 3,
    CAPITALIZE_KEY_BINDING = 4,
    TRANSLIT_KEYS_KEY_BINDING = 5,
    LOWER_KEYS_KEY_BINDING = 6,
    UPPER_KEYS_KEY_BINDING = 7,
    DEEPL_API_KEY = 8,
    TARGET_LANGUAGE = 9,
    SOURCE_LANGUAGE = 10,
    SWAP_LANG_KEY_BINDING = 11,
    TRANSLATE_KEY_BINDING = 12,
    ENABLE_BIND_SUBSETS = 13,
};


static const std::map<std::string, CommandArgType> stringToArgTypeMap = {
    {"--manip-cfg", CommandArgType::MANIP_CFG},
    {"--translator-cfg", CommandArgType::TRANSLATOR_CFG},
    {"--on-windows-start", CommandArgType::ON_WINDOWS_START},
    {"--stop-program-key-binding", CommandArgType::STOP_PROGRAM_KEY_BINDING},
    {"--capitalize-key-binding", CommandArgType::CAPITALIZE_KEY_BINDING},
    {"--translit-keys-key-binding", CommandArgType::TRANSLIT_KEYS_KEY_BINDING},
    {"--lower-keys-key-binding", CommandArgType::LOWER_KEYS_KEY_BINDING},
    {"--upper-keys-key-binding", CommandArgType::UPPER_KEYS_KEY_BINDING},
    {"--deepl-api-key", CommandArgType::DEEPL_API_KEY},
    {"--target-language", CommandArgType::TARGET_LANGUAGE},
    {"--source-language", CommandArgType::SOURCE_LANGUAGE},
    {"--swap-lang-key-binding", CommandArgType::SWAP_LANG_KEY_BINDING},
    {"--translate-key-binding", CommandArgType::TRANSLATE_KEY_BINDING},
    {"--enable-bind-subsets", CommandArgType::ENABLE_BIND_SUBSETS}
};

static const std::map<CommandArgType, std::string> argTypeToStringMap = {
    {CommandArgType::MANIP_CFG, "--manip-cfg"},
    {CommandArgType::TRANSLATOR_CFG, "--translator-cfg"},
    {CommandArgType::ON_WINDOWS_START, "--on-windows-start"},
    {CommandArgType::STOP_PROGRAM_KEY_BINDING, "--stop-program-key-binding"},
    {CommandArgType::CAPITALIZE_KEY_BINDING, "--capitalize-key-binding"},
    {CommandArgType::TRANSLIT_KEYS_KEY_BINDING, "--translit-keys-key-binding"},
    {CommandArgType::LOWER_KEYS_KEY_BINDING, "--lower-keys-key-binding"},
    {CommandArgType::UPPER_KEYS_KEY_BINDING, "--upper-keys-key-binding"},
    {CommandArgType::DEEPL_API_KEY, "--deepl-api-key"},
    {CommandArgType::TARGET_LANGUAGE, "--target-language"},
    {CommandArgType::SOURCE_LANGUAGE, "--source-language"},
    {CommandArgType::SWAP_LANG_KEY_BINDING, "--swap-lang-key-binding"},
    {CommandArgType::TRANSLATE_KEY_BINDING, "--translate-key-binding"},
    {CommandArgType::ENABLE_BIND_SUBSETS, "--enable-bind-subsets"}
};

static std::map<CommandArgType, std::string> argumentDescriptions = {
    {
        CommandArgType::MANIP_CFG,
        "Use this argument to set current manipulator configuration path. Can be passed in set-manip-cfg only"
    },
    {
        CommandArgType::TRANSLATOR_CFG,
        "Use this argument to set current translator configuration path. Can be passed in set-trans-cfg only"
    },
    {
        CommandArgType::ON_WINDOWS_START,
        "Indicates whether program should start with windows or not. Allowed value: T or F"
    },
    {
        CommandArgType::STOP_PROGRAM_KEY_BINDING,
        "Keybinding for stopping the program. Value example: ControlL,AltL (use list-keys) to see allowed keys"
    },
    {
        CommandArgType::CAPITALIZE_KEY_BINDING,
        "Keybinding to use capitalize manipulator. Value example: ControlL,AltL (use list-keys) to see allowed keys"
    },
    {
        CommandArgType::TRANSLIT_KEYS_KEY_BINDING,
        "Language that will be used as target when applying translit manipulator. Allowed values: RU or UK"
    },
    {
        CommandArgType::LOWER_KEYS_KEY_BINDING,
        "Keybinding to use lower case manipulator. Value example: ControlL,AltL (use list-keys) to see allowed keys"
    },
    {
        CommandArgType::UPPER_KEYS_KEY_BINDING,
        "Keybinding to use upper case manipulator. Value example: ControlL,AltL (use list-keys) to see allowed keys"
    },
    {CommandArgType::DEEPL_API_KEY, "Your DeepL api key"},
    {
        CommandArgType::TARGET_LANGUAGE,
        "Target language for translator. Value example: EN  (use list-languages) to see allowed languages"
    },
    {
        CommandArgType::SOURCE_LANGUAGE,
        "Source language for translator. Value example: EN  (use list-languages) to see allowed languages"
    },
    {
        CommandArgType::SWAP_LANG_KEY_BINDING,
        "Keybinding for swapping source and target language. Value example: ControlL,AltL (use list-keys) to see allowed keys"
    },
    {
        CommandArgType::TRANSLATE_KEY_BINDING,
        "Keybinding to apply translation. Value example: ControlL,AltL (use list-keys) to see allowed keys"
    },
    {
        CommandArgType::ENABLE_BIND_SUBSETS,
        "You can decide whether u need to include bind subset (1 bind comb is subset of another) this will make program take more CPU resources. Allowed value: T or F"
    }
};

static CommandArgType string_to_arg(const std::string &str) {
    if (const auto it = stringToArgTypeMap.find(str); it != stringToArgTypeMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Unsupported command argument: " + str);
}

static std::string arg_to_string(const CommandArgType type) {
    if (const auto it = argTypeToStringMap.find(type); it != argTypeToStringMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Unsupported command argument");
}

static bool operator==(const CommandArgType lhs, const std::string &rhs) {
    return arg_to_string(lhs) == rhs;
}

static bool operator!=(const CommandArgType lhs, const std::string &rhs) {
    return !(lhs == rhs);
}

#endif
