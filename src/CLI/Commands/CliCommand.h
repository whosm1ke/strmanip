#ifndef CLICOMMAND_H
#define CLICOMMAND_H
#include <vector>
#include <functional>
#include <stdexcept>
#include <memory>
#include <Enums/CommandArgType.h>
#include "../Pairs/CliPairBase.h"

#define CommandArgs std::vector<std::unique_ptr<CliPairBase>>
#define Callback std::function<void()>

class CliCommand {
public:
    virtual ~CliCommand() = default;

    void setCallback(const Callback &_callback) {
        callback = _callback;
    }

    void setPreCallback(const Callback &_preCallback) {
        preCallback = _preCallback;
    }

    void setPostCallback(const Callback &_postCallback) {
        postCallback = _postCallback;
    }

    void setArgs(CommandArgs &_args) {
        args = std::move(_args);
    }

    void execute() const {
        if (preCallback) {
            preCallback();
        }

        if (callback) {
            callback();
        } else {
            throw std::runtime_error("No callback defined for the command.");
        }

        if (postCallback) {
            postCallback();
        }
    }

    [[nodiscard]] virtual bool supportsArguments() const = 0;

    [[nodiscard]] virtual std::vector<CommandArgType> getSupportedArguments() const { return {}; }

protected:
    Callback callback;
    CommandArgs args;
    Callback preCallback;
    Callback postCallback;
};
#endif
