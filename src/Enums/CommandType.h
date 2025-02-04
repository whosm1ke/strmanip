#ifndef COMMANDTYPE_H
#define COMMANDTYPE_H
#include <string>
#include <map>

enum class CommandType {
    RUN = 0,
    CONFIGURE = 1,
    HELP = 2,
    SET_MANIP_CFG = 3,
    SET_TRAN_CFG = 4,
    LIST_KEYS = 5,
    LIST_LANGUAGES = 6,
    LIST_BINDS = 7,
};


static const std::map<CommandType, std::string> commandTypeToString = {
    {CommandType::RUN, "run"},
    {CommandType::CONFIGURE, "configure"},
    {CommandType::HELP, "help"},
    {CommandType::SET_MANIP_CFG, "set-manip-cfg"},
    {CommandType::SET_TRAN_CFG, "set-trans-cfg"},
    {CommandType::LIST_KEYS, "list-keys"},
    {CommandType::LIST_LANGUAGES, "list-languages"},
    {CommandType::LIST_BINDS, "list-binds"},
};

static const std::map<std::string, CommandType> stringToCommandType = {
    {"run", CommandType::RUN},
    {"configure", CommandType::CONFIGURE},
    {"help", CommandType::HELP},
    {"set-manip-cfg", CommandType::SET_MANIP_CFG},
    {"set-trans-cfg", CommandType::SET_TRAN_CFG},
    {"list-keys", CommandType::LIST_KEYS},
    {"list-languages", CommandType::LIST_LANGUAGES},
    {"list-binds", CommandType::LIST_BINDS}
};

static std::map<CommandType, std::string> commandDescriptions = {
    {CommandType::RUN, "Starts the program."},
    {CommandType::CONFIGURE, "Used to set up configs"},
    {CommandType::HELP, "Displays this message"},
    {CommandType::SET_MANIP_CFG, "Sets manipulator config"},
    {CommandType::SET_TRAN_CFG, "Sets translator config"},
    {CommandType::LIST_KEYS, "Displays all allowed keys"},
    {CommandType::LIST_LANGUAGES, "Displays all allowed languages"},
    {CommandType::LIST_BINDS, "Displays all your binds"},
};

static std::string command_to_string(const CommandType command) {
    if (const auto it = commandTypeToString.find(command); it != commandTypeToString.end()) {
        return it->second;
    }
    throw std::invalid_argument("Unsupported command");
}

static CommandType string_to_command(const std::string &commandStr) {
    if (const auto it = stringToCommandType.find(commandStr); it != stringToCommandType.end()) {
        return it->second;
    }
    throw std::invalid_argument("Unsupported command: " + commandStr);
}

static bool operator==(const CommandType lhs, const std::string &rhs) {
    return command_to_string(lhs) == rhs;
}

static bool operator!=(const CommandType lhs, const std::string &rhs) {
    return !(lhs == rhs);
}


#endif
