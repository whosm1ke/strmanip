#ifndef ENGINE_H
#define ENGINE_H
#include "Abstractions/I_StringManipulator.h"
#include "Manipulators/CapitalizeStringManipulator.h"
#include "Manipulators/LowerStringManipulator.h"
#include "Manipulators/TranslitStringManipulator.h"
#include "Manipulators/UpperStringManipulator.h"
#include "Abstractions/I_StringProvider.h"
#include "Providers/ClipboardStringProvider.h"
#include "Abstractions/I_Translator.h"
#include "Abstractions/I_Logger.h"
#include "Abstractions/I_KeyBinderExecutor.h"
#include "Loggers/FileLogger.h"
#include "Utils/Util.h"
#include <set>
#include <memory>
#include <functional>
#include <Windows.h>
#include <Enums/CommandArgType.h>
#include <Enums/CommandType.h>

#include "Configurations/ManipulatorConfig.h"
#include "Providers/WindowsKeyBinderExecutor.h"
#include "Providers/CustomKeyBinderExecutor.h"
#include "Providers/StopSignal.h"
#include "Translators/DeepLTranslator.h"


#define REGISTER_PATH "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define APP_NAME "StringManipulator"

class Engine {
public:
    static Engine &getInstance() {
        static Engine instance;
        return instance;
    }

    void list_bindings() {
        print_binding("Stop engine bind", global_cfg->get_stop_program_key_binding());
        print_binding("Capitalize key bind", manip_cfg->get_capitalize_key_binding());
        print_binding("Lower key bind", manip_cfg->get_lower_keys_key_binding());
        print_binding("Translit key bind", manip_cfg->get_translit_key_binding());
        print_binding("Upper key bind", manip_cfg->get_upper_keys_key_binding());
        print_binding("Swap language key bind", trans_cfg->get_swap_lang_key_binding());
        print_binding("Translate key bind", trans_cfg->get_translate_key_binding());
    }


    static void display_help_message() {
        std::cout << std::setw(30) << std::left << "Arguments:" << std::endl;

        for (const auto &arg: argumentDescriptions) {
            std::cout << std::setw(30) << std::left << arg_to_string(arg.first)
                    << ": " << arg.second << std::endl;
        }

        std::cout << "\n" << std::setw(30) << std::left << "Commands:" << std::endl;

        for (const auto &cmd: commandDescriptions) {
            std::cout << std::setw(30) << std::left << command_to_string(cmd.first)
                    << ": " << cmd.second << std::endl;
        }
    }

    static void display_keys() {
        constexpr int columnWidth = 25;
        constexpr int columns = 3;
        int count = 0;

        std::cout << std::setw(columnWidth * columns) << std::left << "Available Key Bindings:" << std::endl;

        for (const auto &kv: FromStringToKey) {
            if (kv.second != Key::UNDEFINED) {
                std::cout << std::setw(columnWidth) << std::left << kv.first;
                if (++count % columns == 0) {
                    std::cout << std::endl;
                }
            }
        }

        if (count % columns != 0) {
            std::cout << std::endl;
        }
    }

    static void display_languages() {
        constexpr int columnWidth = 25;
        constexpr int columns = 3;
        int count = 0;

        std::cout << std::setw(columnWidth * columns) << std::left << "Available Languages:" << std::endl;

        for (const auto &kv: StringToLanguage) {
            if (kv.second != Language::UNKNOWN) {
                std::cout << std::setw(columnWidth) << std::left << kv.first;
                if (++count % columns == 0) {
                    std::cout << std::endl;
                }
            }
        }

        if (count % columns != 0) {
            std::cout << std::endl;
        }
    }

    void configure_engine(CommandArgs &args) {
        configure_global_cfg(args);
        configure_manip_cfg(args);
        configure_trans_cfg(args);
    }

    void set_current_manipulator_cfg(const std::string &path) const {
        global_cfg->set_current_manipulator_cfg(path);
        constexpr ConfigIO<GlobalConfig> g_cfg_io;
        g_cfg_io.save(*global_cfg, GLOBAL_CFG_PATH);
    }

    void set_current_translator_cfg(const std::string &path) const {
        global_cfg->set_current_translator_cfg(path);
        constexpr ConfigIO<GlobalConfig> g_cfg_io;
        g_cfg_io.save(*global_cfg, GLOBAL_CFG_PATH);
    }

    void run() {
        cliBoardStringProvider = std::make_shared<ClipboardStringProvider>();
        logger = std::make_shared<FileLogger>();

        if (global_cfg->get_enable_bind_subsets()) {
            keyExecutor = std::make_shared<CustomKeyBinderExecutor>(stopSignal);
        } else {
            keyExecutor = std::make_shared<WindowsKeyBinderExecutor>(stopSignal);
        }

        try {
            register_key_bindings();
        } catch (const std::exception &ex) {
            logger->log(ex.what());
        }
        hide_console();
        keyExecutor->start_listen();
    }

private:
    StopSignal stopSignal;
    std::shared_ptr<GlobalConfig> global_cfg;
    std::string global_cfg_hash;
    std::shared_ptr<ManipulatorConfig> manip_cfg;
    std::string manip_cfg_hash;
    std::shared_ptr<TranslatorConfig> trans_cfg;
    std::string trans_cfg_hash;
    std::shared_ptr<ConfigIO<GlobalConfig> > global_cfg_io;
    std::shared_ptr<ConfigIO<ManipulatorConfig> > manip_cfg_io;
    std::shared_ptr<ConfigIO<TranslatorConfig> > trans_cfg_io;
    std::shared_ptr<I_StringProvider> cliBoardStringProvider;
    std::shared_ptr<I_Logger> logger;
    std::shared_ptr<I_KeyBinderExecutor> keyExecutor;

    static void hide_console() {
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
    }

    void configure_global_cfg(CommandArgs &args) {
        std::map<CommandArgType, std::function<void(const std::unique_ptr<CliPairBase> &)> > global_cfg_args = {
            {
                CommandArgType::MANIP_CFG, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto strPair = dynamic_cast<CliStringPair *>(arg.get());
                    const std::string value = strPair->getValue();
                    global_cfg->set_current_manipulator_cfg(value);
                }
            },
            {
                CommandArgType::TRANSLATOR_CFG, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto strPair = dynamic_cast<CliStringPair *>(arg.get());
                    const std::string value = strPair->getValue();
                    global_cfg->set_current_translator_cfg(value);
                }
            },
            {
                CommandArgType::ON_WINDOWS_START, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto boolPair = dynamic_cast<CliBoolPair *>(arg.get());
                    const bool value = boolPair->getValue();
                    global_cfg->set_run_on_windows_start(value);
                    if (value) {
                        add_to_registry_for_autostart();
                    } else {
                        remove_from_registry_for_autostart();
                    }
                }
            },
            {
                CommandArgType::ENABLE_BIND_SUBSETS, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto boolPair = dynamic_cast<CliBoolPair *>(arg.get());
                    const bool value = boolPair->getValue();
                    global_cfg->set_enable_bind_subsets(value);
                }
            },
            {
                CommandArgType::STOP_PROGRAM_KEY_BINDING, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto vectorOfKeyPair = dynamic_cast<CliVectorOfKeyPair *>(arg.get());
                    const std::set<Key> value = vectorOfKeyPair->getValue();
                    global_cfg->set_stop_program_key_binding(value);
                }
            }
        };

        for (const auto &arg: args) {
            const CommandArgType key = arg->getCommandArgType();
            auto it = global_cfg_args.find(key);
            if (it != global_cfg_args.end()) {
                it->second(arg);
            }
        }

        global_cfg_io->save(*global_cfg, GLOBAL_CFG_PATH);
    }

    void configure_manip_cfg(CommandArgs &args) const {
        std::map<CommandArgType, std::function<void(const std::unique_ptr<CliPairBase> &)> > manip_cfg_args = {
            {
                CommandArgType::CAPITALIZE_KEY_BINDING, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto vectorOfKeyPair = dynamic_cast<CliVectorOfKeyPair *>(arg.get());
                    const std::set<Key> value = vectorOfKeyPair->getValue();
                    manip_cfg->set_capitalize_key_binding(value);
                }
            },
            {
                CommandArgType::TRANSLIT_KEYS_KEY_BINDING, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto vectorOfKeyPair = dynamic_cast<CliVectorOfKeyPair *>(arg.get());
                    const std::set<Key> value = vectorOfKeyPair->getValue();
                    manip_cfg->set_translit_key_binding(value);
                }
            },
            {
                CommandArgType::LOWER_KEYS_KEY_BINDING, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto vectorOfKeyPair = dynamic_cast<CliVectorOfKeyPair *>(arg.get());
                    const std::set<Key> value = vectorOfKeyPair->getValue();
                    manip_cfg->set_lower_keys_key_binding(value);
                }
            },
            {
                CommandArgType::UPPER_KEYS_KEY_BINDING, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto vectorOfKeyPair = dynamic_cast<CliVectorOfKeyPair *>(arg.get());
                    const std::set<Key> value = vectorOfKeyPair->getValue();
                    manip_cfg->set_upper_keys_key_binding(value);
                }
            }
        };

        for (const auto &arg: args) {
            const CommandArgType key = arg->getCommandArgType();
            auto it = manip_cfg_args.find(key);
            if (it != manip_cfg_args.end()) {
                it->second(arg);
            }
        }

        manip_cfg_io->save(*manip_cfg, global_cfg->get_current_manipulator_cfg());
    }

    void configure_trans_cfg(CommandArgs &args) const {
        std::map<CommandArgType, std::function<void(const std::unique_ptr<CliPairBase> &)> > trans_cfg_args = {
            {
                CommandArgType::DEEPL_API_KEY, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto strPair = dynamic_cast<CliStringPair *>(arg.get());
                    const std::string value = strPair->getValue();
                    trans_cfg->set_deepL_api_key(value);
                }
            },
            {
                CommandArgType::TARGET_LANGUAGE, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto languagePair = dynamic_cast<CliLanguagePair *>(arg.get());
                    const Language value = languagePair->getValue();
                    trans_cfg->set_target_language(value);
                }
            },
            {
                CommandArgType::SOURCE_LANGUAGE, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto languagePair = dynamic_cast<CliLanguagePair *>(arg.get());
                    const Language value = languagePair->getValue();
                    trans_cfg->set_source_language(value);
                }
            },
            {
                CommandArgType::SWAP_LANG_KEY_BINDING, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto vectorOfKeyPair = dynamic_cast<CliVectorOfKeyPair *>(arg.get());
                    const std::set<Key> value = vectorOfKeyPair->getValue();
                    trans_cfg->set_swap_lang_key_binding(value);
                }
            },
            {
                CommandArgType::TRANSLATE_KEY_BINDING, [&](const std::unique_ptr<CliPairBase> &arg) {
                    const auto vectorOfKeyPair = dynamic_cast<CliVectorOfKeyPair *>(arg.get());
                    const std::set<Key> value = vectorOfKeyPair->getValue();
                    trans_cfg->set_translate_key_binding(value);
                }
            }
        };

        for (const auto &arg: args) {
            const CommandArgType key = arg->getCommandArgType();
            auto it = trans_cfg_args.find(key);
            if (it != trans_cfg_args.end()) {
                it->second(arg);
            }
        }

        trans_cfg_io->save(*trans_cfg, global_cfg->get_current_translator_cfg());
    }

    static void print_binding(const std::string &bind_name, const std::set<Key> &bind) {
        std::ostringstream oss;
        for (auto it = bind.begin(); it != bind.end(); ++it) {
            if (it != bind.begin()) {
                oss << " + ";
            }
            oss << key_to_string(*it);
        }
        std::cout << std::left << std::setw(30) << bind_name << " " << oss.str() << std::endl;
    }

    void register_key_bindings() {
        keyExecutor->register_combination_action(global_cfg->get_stop_program_key_binding(), [this]() {
            stopSignal.signal_stop();
        });

        keyExecutor->register_combination_action(trans_cfg->get_swap_lang_key_binding(), [this]() {
            try {
                swap_languages();
            } catch (const std::exception &ex) {
                logger->log(ex.what());
            }
        });

        keyExecutor->register_combination_action(trans_cfg->get_translate_key_binding(), [this]() {
            try {
                const std::string str = cliBoardStringProvider->get_string();
                const auto translated = apply_string_translation(str, DeepLTranslator{});
                cliBoardStringProvider->set_string(translated);
            } catch (const std::exception &ex) {
                logger->log(ex.what());
            }
        });

        keyExecutor->register_combination_action(manip_cfg->get_capitalize_key_binding(), [this]() {
            try {
                std::string str = cliBoardStringProvider->get_string();
                apply_string_manipulation(str, CapitalizeStringManipulator{});
                cliBoardStringProvider->set_string(str);
            } catch (const std::exception &ex) {
                logger->log(ex.what());
            }
        });

        keyExecutor->register_combination_action(manip_cfg->get_lower_keys_key_binding(), [this]() {
            try {
                std::string str = cliBoardStringProvider->get_string();
                apply_string_manipulation(str, LowerStringManipulator{});
                cliBoardStringProvider->set_string(str);
            } catch (const std::exception &ex) {
                logger->log(ex.what());
            }
        });

        keyExecutor->register_combination_action(manip_cfg->get_translit_key_binding(), [this]() {
            try {
                std::string str = cliBoardStringProvider->get_string();
                apply_string_manipulation(str, TranslitStringManipulator{});
                cliBoardStringProvider->set_string(str);
            } catch (const std::exception &ex) {
                logger->log(ex.what());
            }
        });

        keyExecutor->register_combination_action(manip_cfg->get_upper_keys_key_binding(), [this]() {
            try {
                std::string str = cliBoardStringProvider->get_string();
                apply_string_manipulation(str, UpperStringManipulator{});
                cliBoardStringProvider->set_string(str);
            } catch (const std::exception &ex) {
                logger->log(ex.what());
            }
        });
    }

    static void apply_string_manipulation(std::string &str, const I_StringManipulator &manipulator) {
        manipulator.manipulate(str);
    }

    static std::string apply_string_translation(const std::string &str, const I_Translator &translator) {
        std::future<std::string> future_translation = translator.translate_async(str);
        std::string translated_text = future_translation.get();
        return translated_text;
    }

    void swap_languages() {
        constexpr ConfigIO<TranslatorConfig> trans_io;
        const auto global_cfg = get_or_create_global_config();
        const auto trans_cfg = get_or_create_translator_config();
        const auto temp_source_lang = trans_cfg->get_source_language();
        trans_cfg->set_source_language(trans_cfg->get_target_language());
        trans_cfg->set_target_language(temp_source_lang);
        trans_io.save(*trans_cfg, global_cfg->get_current_translator_cfg());
    }


    Engine() {
        global_cfg = get_or_create_global_config();
        manip_cfg = get_or_create_manipulator_config();
        trans_cfg = get_or_create_translator_config();
        global_cfg_hash = global_cfg->get_config_hash();
        manip_cfg_hash = manip_cfg->get_config_hash();
        trans_cfg_hash = trans_cfg->get_config_hash();
        global_cfg_io = std::make_shared<ConfigIO<GlobalConfig> >();
        manip_cfg_io = std::make_shared<ConfigIO<ManipulatorConfig> >();
        trans_cfg_io = std::make_shared<ConfigIO<TranslatorConfig> >();
    }

    ~Engine() = default;

    Engine(const Engine &) = delete;

    Engine &operator=(const Engine &) = delete;

    std::shared_ptr<ManipulatorConfig> get_or_create_manipulator_config() const {
        const auto isGlobalCfgExist = check_if_global_cfg_present();

        if (isGlobalCfgExist.first) {
            const std::string &manip_cfg_path = isGlobalCfgExist.second->get_current_manipulator_cfg();

            if (!manip_cfg_path.empty() && std::filesystem::exists(manip_cfg_path)) {
                auto manip_cfg = manip_cfg_io->read(manip_cfg_path);
                return std::make_shared<ManipulatorConfig>(manip_cfg);
            }
            ManipulatorConfig new_manip_cfg{};

            isGlobalCfgExist.second->set_current_manipulator_cfg(BASE_MANIP_CFG_PATH);

            manip_cfg_io->save(new_manip_cfg, BASE_MANIP_CFG_PATH);

            global_cfg_io->save(*isGlobalCfgExist.second, GLOBAL_CFG_PATH);

            return std::make_shared<ManipulatorConfig>(new_manip_cfg);
        }
        throw std::runtime_error("Global config not found.");
    }

    std::shared_ptr<TranslatorConfig> get_or_create_translator_config() const {
        const auto isGlobalCfgExist = check_if_global_cfg_present();

        if (isGlobalCfgExist.first) {
            const std::string &trans_cfg_path = isGlobalCfgExist.second->get_current_translator_cfg();

            if (!trans_cfg_path.empty() && std::filesystem::exists(trans_cfg_path)) {
                auto trans_cfg = trans_cfg_io->read(trans_cfg_path);
                return std::make_shared<TranslatorConfig>(trans_cfg);
            }
            TranslatorConfig new_trans_cfg;

            isGlobalCfgExist.second->set_current_translator_cfg(BASE_TRANS_CFG_PATH);

            trans_cfg_io->save(new_trans_cfg, BASE_TRANS_CFG_PATH);

            global_cfg_io->save(*isGlobalCfgExist.second, GLOBAL_CFG_PATH);

            return std::make_shared<TranslatorConfig>(new_trans_cfg);
        }
        throw std::runtime_error("Global config not found.");
    }

    std::shared_ptr<GlobalConfig> get_or_create_global_config() const {
        const auto isGlobalCfgExist = check_if_global_cfg_present();

        if (isGlobalCfgExist.first) {
            return isGlobalCfgExist.second;
        }
        GlobalConfig new_global_cfg;

        new_global_cfg.set_current_translator_cfg(BASE_TRANS_CFG_PATH);
        new_global_cfg.set_current_manipulator_cfg(BASE_MANIP_CFG_PATH);
        global_cfg_io->save(new_global_cfg, GLOBAL_CFG_PATH);

        return std::make_shared<GlobalConfig>(new_global_cfg);
    }

    static void add_to_registry_for_autostart() {
        const std::string exePath = Util::get_executable_path() + " run";
        const std::string &appName{APP_NAME};
        HKEY hKey;
        if (RegOpenKeyExA(HKEY_CURRENT_USER, REGISTER_PATH, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
            RegSetValueExA(hKey, appName.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE *>(exePath.c_str()),
                           exePath.size() + 1);
            RegCloseKey(hKey);
        }
    }

    static void remove_from_registry_for_autostart() {
        const std::string &appName{APP_NAME};
        HKEY hKey;
        if (RegOpenKeyExA(HKEY_CURRENT_USER, REGISTER_PATH, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
            RegDeleteValueA(hKey, appName.c_str());
            RegCloseKey(hKey);
        }
    }

    std::pair<bool, std::shared_ptr<GlobalConfig> > check_if_global_cfg_present() const {
        try {
            auto cfg = global_cfg_io->read(GLOBAL_CFG_PATH);
            return std::make_pair(true, std::make_shared<GlobalConfig>(cfg));
        } catch (...) {
            return std::make_pair(false, nullptr);
        }
    }
};


#endif
