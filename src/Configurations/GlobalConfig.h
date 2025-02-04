#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include <Utils/Util.h>

#include "../Abstractions/I_Config.h"
#include "Enums/Key.h"

const std::string GLOBAL_CFG_PATH = Util::get_executable_path() + "\\" + "global.json";

class GlobalConfig final : public I_Config {
    bool run_on_windows_start{false};
    bool enable_bind_subsets{false};
    std::string current_translator_cfg{};
    std::string current_manipulator_cfg{};
    std::set<Key> stop_program_key_binding{};

    void validate_json(const nlohmann::json &j) const override {
        if (!j.contains("current_translator_cfg")) {
            throw std::runtime_error("Missing 'current_translator_cfg' field.");
        }
        if (!j.contains("current_manipulator_cfg")) {
            throw std::runtime_error("Missing 'current_manipulator_cfg' field.");
        }

        if (!j.contains("run_on_windows_start")) {
            throw std::runtime_error("Missing 'run_on_windows_start' field.");
        }

        if (!j.at("run_on_windows_start").is_boolean()) {
            throw std::runtime_error("Invalid 'run_on_windows_start' field.");
        }
        if (!j.contains("enable_bind_subsets")) {
            throw std::runtime_error("Missing 'enable_bind_subsets' field.");
        }

        if (!j.at("enable_bind_subsets").is_boolean()) {
            throw std::runtime_error("Invalid 'enable_bind_subsets' field.");
        }

        if (!j.contains("stop_program_key_binding")) {
            throw std::runtime_error("Missing 'stop_program_key_binding' field.");
        }

        if (!j.at("stop_program_key_binding").is_array()) {
        }
    }

public:
    GlobalConfig(const GlobalConfig &source) = default;

    GlobalConfig(GlobalConfig &&source) = default;

    GlobalConfig(const bool &run_on_windows_start,
                 const bool &enable_bind_subsets,
                 const std::string &current_translator_cfg,
                 const std::string &current_manipulator_cfg,
                 const std::set<Key> &stop_program_key_binding)
        : run_on_windows_start(run_on_windows_start),
          enable_bind_subsets(enable_bind_subsets),
          current_translator_cfg(current_translator_cfg),
          current_manipulator_cfg(current_manipulator_cfg),
          stop_program_key_binding(stop_program_key_binding) {
    }

    GlobalConfig() = default;

    ~GlobalConfig() override = default;

    [[nodiscard]] std::string get_current_translator_cfg() const { return current_translator_cfg; }
    [[nodiscard]] std::string get_current_manipulator_cfg() const { return current_manipulator_cfg; }
    [[nodiscard]] bool get_run_on_windows_start() const { return run_on_windows_start; }
    [[nodiscard]] bool get_enable_bind_subsets() const { return enable_bind_subsets; }
    [[nodiscard]] const std::set<Key> &get_stop_program_key_binding() const { return stop_program_key_binding; }

    void set_run_on_windows_start(const bool value) {
        run_on_windows_start = value;
    }

    void set_enable_bind_subsets(const bool value) {
        enable_bind_subsets = value;
    }

    void set_current_translator_cfg(const std::string &path) {
        current_translator_cfg = path;
    }

    void set_current_manipulator_cfg(const std::string &path) {
        current_manipulator_cfg = path;
    }

    void set_stop_program_key_binding(const std::set<Key> &keys) {
        stop_program_key_binding = keys;
    }

    void to_json(nlohmann::json &j) const override {
        nlohmann::json stop_program_key_binding_json = nlohmann::json::array();
        for (const auto &key: stop_program_key_binding) {
            stop_program_key_binding_json.push_back(key_to_string(key));
        }

        j = nlohmann::json{
            {"run_on_windows_start", run_on_windows_start},
            {"enable_bind_subsets", enable_bind_subsets},
            {"current_translator_cfg", current_translator_cfg},
            {"current_manipulator_cfg", current_manipulator_cfg},
            {"stop_program_key_binding", stop_program_key_binding_json},
        };
    }

    void from_json(const nlohmann::json &j) override {
        validate_json(j);

        stop_program_key_binding.clear();
        for (const auto &item: j.at("stop_program_key_binding")) {
            stop_program_key_binding.insert(string_to_key(item.get<std::string>()));
        }

        j.at("run_on_windows_start").get_to(run_on_windows_start);
        j.at("enable_bind_subsets").get_to(enable_bind_subsets);
        j.at("current_translator_cfg").get_to(current_translator_cfg);
        j.at("current_manipulator_cfg").get_to(current_manipulator_cfg);
    }

    [[nodiscard]] std::string get_config_hash() const override {
        nlohmann::json j;
        to_json(j);
        const std::string json_str = j.dump();

        constexpr std::hash<std::string> hasher;
        const size_t hash_value = hasher(json_str);

        std::ostringstream hex_stream;
        hex_stream << std::hex << hash_value;

        return hex_stream.str();
    }
};
#endif
