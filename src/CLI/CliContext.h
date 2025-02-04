#ifndef CLICONTEXT_H
#define CLICONTEXT_H
#include "CommandsAndArgs.h"
#include <vector>
#include <memory>
#include <functional>

class CliContext {
public:
    CliContext(const int argc, char *argv[]) : cliCommand(nullptr) {
        if (argc <= 1) {
            throw std::invalid_argument("No command provided.");
        }
        parse_command(argc, argv);

        if (cliCommand == nullptr) {
            throw std::invalid_argument("No command provided.");
        }

        parse_arguments(argc, argv);
        setup_command_args();
    }


    void execute() {
        if (cliCommand == nullptr) {
            throw std::invalid_argument("No command provided.");
        }
        if (dynamic_cast<const InteraptableCliCommand *>(cliCommand.get()) != nullptr) {
            cliCommand->execute();
        } else {
            check_single_instance();
            cliCommand->execute();
        }
    }

private:
    CommandArgs cliArgs;
    std::unique_ptr<CliCommand> cliCommand;

    static void check_single_instance() {
        const HANDLE semaphore = CreateSemaphoreA(
            nullptr,
            1,
            1,
            "UniqueSemaphore"
        );

        if (semaphore == nullptr) {
            throw std::runtime_error("Another instance of the program is already running.");
        }

        if (DWORD dwWaitResult = WaitForSingleObject(semaphore, 0); dwWaitResult == WAIT_TIMEOUT) {
            CloseHandle(semaphore);
            throw std::runtime_error("Another instance of the program is already running.");
        }
    }

    void parse_arguments(const int argc, char *argv[]) {
        constexpr int start = 2;
        for (int i = start; i < argc; ++i) {
            std::string arg = argv[i];

            if (arg.find("--") == 0) {
                if (i + 1 < argc) {
                    std::string value = argv[i + 1];
                    auto it = argsMap.find(string_to_arg(arg));
                    if (it != argsMap.end()) {
                        cliArgs.push_back(it->second(arg + " " + value));
                        i++;
                    } else {
                        throw std::invalid_argument("Unknown argument: " + arg);
                    }
                } else {
                    throw std::invalid_argument("Missing value for argument: " + arg);
                }
            } else {
                throw std::invalid_argument("Unknown argument: " + arg);
            }
        }
    }

    void parse_command(const int argc, char *argv[]) {
        if (cliCommand == nullptr) {
            if (argc <= 0) {
                throw std::invalid_argument("No command provided.");
            }

            const std::string cmd = argv[1];

            if (auto it = commandsMap.find(string_to_command(cmd)); it != commandsMap.end()) {
                cliCommand = it->second();
            } else {
                throw std::invalid_argument("Command not found: " + cmd);
            }
        } else {
            throw std::invalid_argument("Only one command is allowed, multiple commands are not supported.");
        }
    }

    void setup_command_args() {
        if (cliCommand == nullptr) {
            return;
        }

        if (!cliCommand->supportsArguments()) {
            if (!cliArgs.empty()) {
                throw std::invalid_argument("Command does not support arguments.");
            }
            return;
        }

        std::vector<CommandArgType> allowedArgs = cliCommand->getSupportedArguments();

        for (const auto &arg: cliArgs) {
            if (std::find(allowedArgs.begin(), allowedArgs.end(), arg->getCommandArgType()) == allowedArgs.end()) {
                throw std::invalid_argument("Argument " + arg->getArgName() + " is not allowed for this command.");
            }
        }

        if (allowedArgs.empty()) {
            throw std::invalid_argument("Command must be called with at least one argument.");
        }

        cliCommand->setArgs(cliArgs);
    }
};


#endif
