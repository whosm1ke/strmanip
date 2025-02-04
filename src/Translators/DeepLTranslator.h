#ifndef DEEPLTRANSLATOR_H
#define DEEPLTRANSLATOR_H
#include <string>
#include "Abstractions/I_Translator.h"
#include "Configurations/ConfigIO.h"
#include "Configurations/GlobalConfig.h"
#include "Configurations/TranslatorConfig.h"
#include "Enums/Language.h"
#include <cpr/cpr.h>
#include <cpr/error.h>

class DeepLTranslator : public I_Translator {
    const std::string api_endpoint = "https://api-free.deepl.com/v2/translate";

public:
    explicit DeepLTranslator()
        : I_Translator("", Language::UNKNOWN, Language::UNKNOWN) {
        constexpr ConfigIO<GlobalConfig> global_config_io;
        const GlobalConfig global_cfg = global_config_io.read(GLOBAL_CFG_PATH);
        constexpr ConfigIO<TranslatorConfig> trans_config_io;
        const TranslatorConfig trans_cfg = trans_config_io.read(global_cfg.get_current_translator_cfg());

        api_key = trans_cfg.get_deepL_api_key();
        source_lang = trans_cfg.get_source_language();
        target_lang = trans_cfg.get_target_language();
    }

    DeepLTranslator(const std::string &apiKey,
                    const Language &sourceLang,
                    const Language &targetLang)
        : I_Translator(apiKey, sourceLang, targetLang) {
    }

    std::future<std::string> translate_async(const std::string &text) const override {
        return std::async(std::launch::async, [this, text]() {
            auto translated_text_pair = send_translation_request(text, target_lang);

            if (translated_text_pair.second != target_lang) {
                return translated_text_pair.first;
            }

            translated_text_pair = send_translation_request(text, source_lang);
            return translated_text_pair.first;
        });
    }

private:
    std::pair<std::string, Language> send_translation_request(const std::string &text, const Language lang
    ) const {
        try {
            cpr::Parameters parameters = {
                {"text", text},
                {"target_lang", language_to_string(lang)}
            };

            cpr::Header headers = {{"Authorization", "DeepL-Auth-Key " + api_key}};
            cpr::Response response = cpr::Post(cpr::Url{api_endpoint}, parameters, headers);

            if (response.status_code != 200) {
                const auto jsonResponse = nlohmann::json::parse(response.text);
                const auto message = jsonResponse["message"].get<std::string>();
                throw std::runtime_error("DeepL Error: " + message);
            }

            auto jsonResponse = nlohmann::json::parse(response.text);
            const auto detected_source_language = jsonResponse["translations"][0]["detected_source_language"].get<
                std::string>();
            return std::make_pair(jsonResponse["translations"][0]["text"].get<std::string>(),
                                  string_to_language(detected_source_language));
        } catch (const cpr::Error &e) {
            throw std::runtime_error("Network error: " + e.message);
        } catch (const std::exception &e) {
            throw std::runtime_error("Error during translation request: " + std::string(e.what()));
        }
    }
};
#endif
