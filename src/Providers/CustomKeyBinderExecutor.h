#ifndef CUSTOMKEYBINDEREXECUTOR_H
#define CUSTOMKEYBINDEREXECUTOR_H
#include <windows.h>
#include <vector>
#include <iostream>
#include <functional>
#include <Enums/Key.h>
#include <set>
#include <string>
#include <Abstractions/I_KeyBinderExecutor.h>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "StopSignal.h"

class CustomKeyBinderExecutor final : public I_KeyBinderExecutor {
public:
    explicit CustomKeyBinderExecutor(StopSignal &stopSignal)
        : I_KeyBinderExecutor(stopSignal) {
    }

    using KeyCombinationAction = std::pair<std::set<Key>, Action>;

    void register_combination_action(const std::set<Key> &combination, Action action) override {
        for (const auto &existing_combination: combinations_actions) {
            if (existing_combination.first == combination) {
                std::ostringstream error_message;
                error_message << "Combination already registered. It will be ignored: ";
                for (const auto &key: combination) {
                    error_message << key_to_string(key) << " + ";
                }
                std::string message = error_message.str();
                message = message.substr(0, message.size() - 3);
                throw std::runtime_error(message);
            }
        }
        combinations_actions.emplace_back(combination, action);
        for (const auto &key: combination) {
            available_keys.insert(key);
        }
    }

    void start_listen() override {
        std::set<Key> pressedKeys;
        KeyCombinationAction *matchedCombination = nullptr;
        while (!stopSignal.is_stopped()) {
            for (const auto &key: available_keys) {
                if (is_key_pressed(key)) {
                    pressedKeys.insert(key);
                }
            }
            if (pressedKeys.empty()) {
                continue;
            }
            KeyCombinationAction *newMatchedCombination = nullptr;
            for (auto &combinationAction: combinations_actions) {
                if (is_combination_included(combinationAction.first, pressedKeys)) {
                    if (!newMatchedCombination || combinationAction.first.size() > newMatchedCombination->first.
                        size()) {
                        newMatchedCombination = &combinationAction;
                    }
                }
            }
            if (newMatchedCombination) {
                matchedCombination = newMatchedCombination;
            }
            if (matchedCombination) {
                const bool allCombinationKeysReleased = std::all_of(matchedCombination->first.begin(),
                                                                    matchedCombination->first.end(),
                                                                    [this](const Key key) {
                                                                        return !is_key_pressed(key);
                                                                    });
                if (allCombinationKeysReleased) {
                    matchedCombination->second();
                    pressedKeys.clear();
                    matchedCombination = nullptr;
                }
            }
            const bool allPressedKeysReleased = std::all_of(pressedKeys.begin(), pressedKeys.end(),
                                                            [this](const Key key) { return !is_key_pressed(key); });
            if (allPressedKeysReleased) {
                pressedKeys.clear();
            }
            Sleep(20);
        }
    }

    void clear_all_bindings() override {
        combinations_actions.clear();
        available_keys.clear();
    }

    ~CustomKeyBinderExecutor() override {
        CustomKeyBinderExecutor::clear_all_bindings();
    }

private:
    static bool is_key_pressed(Key key) {
        const SHORT keyState = GetAsyncKeyState(static_cast<int>(key));
        return (keyState & 0x8000) != 0;
    }

    static bool is_combination_included(const std::set<Key> &combination, const std::set<Key> &pressedKeys) {
        return std::includes(pressedKeys.begin(), pressedKeys.end(), combination.begin(), combination.end());
    }

    std::vector<KeyCombinationAction> combinations_actions;
    std::set<Key> available_keys;
};
#endif
