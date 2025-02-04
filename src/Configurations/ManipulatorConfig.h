#ifndef MANIPULATORCONFIG_H
#define MANIPULATORCONFIG_H
#include <string>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include "../Abstractions/I_Config.h"
#include "Enums/Key.h"
#include "Enums/Language.h"

const std::string BASE_MANIP_CFG_PATH = std::filesystem::current_path().string() + "\\" + "manip.json";

class ManipulatorConfig final : public I_Config {
    std::set<Key> capitalize_key_binding{};
    std::set<Key> lower_keys_key_binding{};
    std::set<Key> upper_keys_key_binding{};
    std::set<Key> translit_key_binding{};

    void validate_json(const nlohmann::json &j) const override {
        if (!j.contains("capitalize_key_binding")) {
            throw std::runtime_error("Missing 'capitalize_key_binding' field.");
        }

        if (!j.at("capitalize_key_binding").is_array()) {
            throw std::runtime_error("Invalid 'capitalize_key_binding' field.");
        }

        if (!j.contains("lower_keys_key_binding")) {
            throw std::runtime_error("Missing 'lower_keys_key_binding' field.");
        }

        if (!j.at("lower_keys_key_binding").is_array()) {
            throw std::runtime_error("Invalid 'lower_keys_key_binding' field.");
        }

        if (!j.contains("upper_keys_key_binding")) {
            throw std::runtime_error("Missing 'upper_keys_key_binding' field.");
        }

        if (!j.at("upper_keys_key_binding").is_array()) {
            throw std::runtime_error("Invalid 'upper_keys_key_binding' field.");
        }

        if (!j.contains("translit_key_binding")) {
            throw std::runtime_error("Missing 'translit_key_binding' field.");
        }

        if (!j.at("translit_key_binding").is_array()) {
            throw std::runtime_error("Invalid 'translit_key_binding' field.");
        }
    }

public:
    ManipulatorConfig(const ManipulatorConfig &source) = default;

    ManipulatorConfig() = default;

    ManipulatorConfig(const std::set<Key> &capitalize_key_binding,
                      const std::set<Key> &lower_keys_key_binding,
                      const std::set<Key> &upper_keys_key_binding,
                      const std::set<Key> &translit_key_binding)
        : capitalize_key_binding(capitalize_key_binding),
          lower_keys_key_binding(lower_keys_key_binding),
          upper_keys_key_binding(upper_keys_key_binding),
          translit_key_binding(translit_key_binding) {
    }

    ManipulatorConfig(ManipulatorConfig &&source) = default;

    ~ManipulatorConfig() override = default;

    [[nodiscard]] const std::set<Key> &get_capitalize_key_binding() const { return capitalize_key_binding; }
    [[nodiscard]] const std::set<Key> &get_lower_keys_key_binding() const { return lower_keys_key_binding; }
    [[nodiscard]] const std::set<Key> &get_upper_keys_key_binding() const { return upper_keys_key_binding; }
    [[nodiscard]] const std::set<Key> &get_translit_key_binding() const { return translit_key_binding; }

    void set_capitalize_key_binding(const std::set<Key> &keys) {
        capitalize_key_binding = keys;
    }

    void set_lower_keys_key_binding(const std::set<Key> &keys) {
        lower_keys_key_binding = keys;
    }

    void set_upper_keys_key_binding(const std::set<Key> &keys) {
        upper_keys_key_binding = keys;
    }

    void set_translit_key_binding(const std::set<Key> &keys) {
        translit_key_binding = keys;
    }


    void to_json(nlohmann::json &j) const override {
        nlohmann::json capitalize_key_binding_json = nlohmann::json::array();
        for (const auto &key: capitalize_key_binding) {
            capitalize_key_binding_json.push_back(key_to_string(key));
        }

        nlohmann::json lower_keys_key_binding_json = nlohmann::json::array();
        for (const auto &key: lower_keys_key_binding) {
            lower_keys_key_binding_json.push_back(key_to_string(key));
        }

        nlohmann::json upper_keys_key_binding_json = nlohmann::json::array();
        for (const auto &key: upper_keys_key_binding) {
            upper_keys_key_binding_json.push_back(key_to_string(key));
        }

        nlohmann::json translit_key_binding_json = nlohmann::json::array();
        for (const auto &key: translit_key_binding) {
            translit_key_binding_json.push_back(key_to_string(key));
        }

        j = nlohmann::json{
            {"capitalize_key_binding", capitalize_key_binding_json},
            {"lower_keys_key_binding", lower_keys_key_binding_json},
            {"upper_keys_key_binding", upper_keys_key_binding_json},
            {"translit_key_binding", translit_key_binding_json}
        };
    }

    void from_json(const nlohmann::json &j) override {
        validate_json(j);

        capitalize_key_binding.clear();
        for (const auto &item: j.at("capitalize_key_binding")) {
            capitalize_key_binding.insert(string_to_key(item.get<std::string>()));
        }

        lower_keys_key_binding.clear();
        for (const auto &item: j.at("lower_keys_key_binding")) {
            lower_keys_key_binding.insert(string_to_key(item.get<std::string>()));
        }

        upper_keys_key_binding.clear();
        for (const auto &item: j.at("upper_keys_key_binding")) {
            upper_keys_key_binding.insert(string_to_key(item.get<std::string>()));
        }

        translit_key_binding.clear();
        for (const auto &item: j.at("translit_key_binding")) {
            translit_key_binding.insert(string_to_key(item.get<std::string>()));
        }
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
