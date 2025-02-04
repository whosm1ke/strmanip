#ifndef TRANSLATORCONFIG_H
#define TRANSLATORCONFIG_H
#include <string>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include "../Abstractions/I_Config.h"
#include "Enums/Key.h"
#include "Enums/Language.h"

const std::string BASE_TRANS_CFG_PATH = std::filesystem::current_path().string() + "\\" + "trans.json";

class TranslatorConfig final : public I_Config {
private:
    std::string deepL_api_key{};
    Language source_language{Language::EN};
    Language target_language{Language::EN};
    std::set<Key> translate_key_binding{};
    std::set<Key> swap_lang_key_binding{};

    void validate_json(const nlohmann::json &j) const override {
        if (!j.contains("deepL_api_key")) {
            throw std::runtime_error("Missing 'deepL_api_key' field.");
        }
        if (!j.contains("source_language")) {
            throw std::runtime_error("Missing 'source_language' field.");
        }
        if (!j.contains("target_language")) {
            throw std::runtime_error("Missing 'target_language' field.");
        }

        if (!j.contains("translate_key_binding")) {
            throw std::runtime_error("Missing 'translate_key_binding' field.");
        }

        if (!j.at("translate_key_binding").is_array()) {
            throw std::runtime_error("Invalid 'translate_key_binding' field.");
        }

        if (!j.contains("swap_lang_key_binding")) {
            throw std::runtime_error("Missing 'swap_lang_key_binding' field.");
        }

        if (!j.at("swap_lang_key_binding").is_array()) {
            throw std::runtime_error("Invalid 'swap_lang_key_binding' field.");
        }
    }

public:
    TranslatorConfig(const TranslatorConfig &source) = default;

    TranslatorConfig() = default;

    TranslatorConfig(const std::string &deepL_api_key,
                     const Language &source_lang,
                     const Language &target_lang,
                     const std::set<Key> &translate_key_binding,
                     const std::set<Key> &swap_lang_key_binding)
        : deepL_api_key(deepL_api_key),
          source_language(source_lang),
          target_language(target_lang),
          translate_key_binding(translate_key_binding),
          swap_lang_key_binding(swap_lang_key_binding) {
    }

    TranslatorConfig(TranslatorConfig &&source) = default;

    ~TranslatorConfig() override = default;

    [[nodiscard]] std::string get_deepL_api_key() const { return deepL_api_key; }
    [[nodiscard]] Language get_source_language() const { return source_language; }
    [[nodiscard]] Language get_target_language() const { return target_language; }
    [[nodiscard]] const std::set<Key> &get_translate_key_binding() const { return translate_key_binding; }
    [[nodiscard]] const std::set<Key> &get_swap_lang_key_binding() const { return swap_lang_key_binding; }

    void set_deepL_api_key(const std::string &key) {
        deepL_api_key = key;
    }

    void set_source_language(const Language lang) {
        source_language = lang;
    }

    void set_target_language(const Language lang) {
        target_language = lang;
    }

    void set_translate_key_binding(const std::set<Key> &keys) {
        translate_key_binding = keys;
    }

    void set_swap_lang_key_binding(const std::set<Key> &keys) {
        swap_lang_key_binding = keys;
    }


    void to_json(nlohmann::json &j) const override {
        nlohmann::json translate_keys_json = nlohmann::json::array();
        for (const auto &key: translate_key_binding) {
            translate_keys_json.push_back(key_to_string(key));
        }

        nlohmann::json swap_keys_json = nlohmann::json::array();
        for (const auto &key: swap_lang_key_binding) {
            swap_keys_json.push_back(key_to_string(key));
        }

        j = nlohmann::json{
            {"deepL_api_key", deepL_api_key},
            {"source_language", language_to_string(source_language)},
            {"target_language", language_to_string(target_language)},
            {"translate_key_binding", translate_keys_json},
            {"swap_lang_key_binding", swap_keys_json},

        };
    }

    void from_json(const nlohmann::json &j) override {
        validate_json(j);

        j.at("deepL_api_key").get_to(deepL_api_key);

        source_language = string_to_language(j.at("source_language").get<std::string>());
        target_language = string_to_language(j.at("target_language").get<std::string>());

        translate_key_binding.clear();
        for (const auto &item: j.at("translate_key_binding")) {
            translate_key_binding.insert(string_to_key(item.get<std::string>()));
        }

        swap_lang_key_binding.clear();
        for (const auto &item: j.at("swap_lang_key_binding")) {
            swap_lang_key_binding.insert(string_to_key(item.get<std::string>()));
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
