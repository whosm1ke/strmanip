#ifndef I_KEYBINDEREXECUTOR_H
#define I_KEYBINDEREXECUTOR_H
#include "Providers/StopSignal.h"

class I_KeyBinderExecutor {
public:
    using Action = std::function<void()>;

    virtual void register_combination_action(const std::set<Key> &combination, Action action) = 0;

    virtual void start_listen() = 0;

    virtual void clear_all_bindings() = 0;

    virtual ~I_KeyBinderExecutor() = default;

    explicit I_KeyBinderExecutor(StopSignal &stopSignal): stopSignal(stopSignal) {
    };

protected:
    StopSignal &stopSignal;
};
#endif
