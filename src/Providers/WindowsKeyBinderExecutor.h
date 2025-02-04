#ifndef KEYCOMBINATIONEXECUTOR_H
#define KEYCOMBINATIONEXECUTOR_H
#include <windows.h>
#include <iostream>
#include <functional>
#include <Enums/Key.h>
#include <Abstractions/I_KeyBinderExecutor.h>

#include "StopSignal.h"


class WindowsKeyBinderExecutor final : public I_KeyBinderExecutor {
public:
    explicit WindowsKeyBinderExecutor(StopSignal &stopSignal)
        : I_KeyBinderExecutor(stopSignal) {
    }

    void register_combination_action(const std::set<Key> &combination, const Action action) override {
        if (combination.empty()) return;

        UINT modifiers = 0;
        UINT key = 0;

        for (Key k: combination) {
            switch (k) {
                case Key::CTRL: modifiers |= MOD_CONTROL;
                    break;
                case Key::ALT: modifiers |= MOD_ALT;
                    break;
                case Key::SHIFT: modifiers |= MOD_SHIFT;
                    break;
                case Key::WIN: modifiers |= MOD_WIN;
                    break;
                default:
                    if (key == 0) key = static_cast<UINT>(k);
                    break;
            }
        }

        if (key == 0) return;

        const int hotkeyID = nextHotkeyID++;

        if (!RegisterHotKey(NULL, hotkeyID, modifiers, key)) {
            throw std::runtime_error("Combination is a subset of another. Skipping registration.");
        }

        hotkeyActions[hotkeyID] = action;
    }

    void start_listen() override {
        MSG msg;
        while (!stopSignal.is_stopped()) {
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_HOTKEY) {
                    int hotkeyID = msg.wParam;
                    auto it = hotkeyActions.find(hotkeyID);
                    if (it != hotkeyActions.end()) {
                        it->second();
                    }
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            Sleep(10);
        }
    }

    void clear_all_bindings() override {
        for (auto &[id, _]: hotkeyActions) {
            UnregisterHotKey(NULL, id);
        }
    }

    ~WindowsKeyBinderExecutor() override {
        WindowsKeyBinderExecutor::clear_all_bindings();
    }

private:
    std::unordered_map<int, Action> hotkeyActions;
    int nextHotkeyID = 1;
};


#endif
