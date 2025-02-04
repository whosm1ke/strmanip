#ifndef TRANSLITSTRINGMANIPULATOR_H
#define TRANSLITSTRINGMANIPULATOR_H

#define MAX_CHARS_TO_ANALYZE 100
#include "Abstractions/I_StringManipulator.h"
#include "Utils/Encoding.h"
#include <algorithm>
#include <regex>
#include <Enums/Language.h>

#include "Configurations/ConfigIO.h"

static const std::wstring english_vector{
    L"qwertyuiop[]asdfghjkl;'zxcvbnm,./`QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?~!@#$%^&*()"
};
static const std::wstring ukrainian_vector{
    L"йцукенгшщзхїфівапролджєячсмитьбю.'ЙЦУКЕНГШЩЗХЇФІВАПРОЛДЖЄЯЧСМИТЬБЮ,₴!\"№;%:?*()"
};
static const std::wstring russian_vector{
    L"йцукенгшщзхъфывапролджэячсмитьбю.ёЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ,Ё!\"№;%:?*()"
};


class TranslitStringManipulator final : public I_StringManipulator {
    static Language detect_source_language(const std::wstring &str) {
        const std::wregex cyrillic_pattern(L"[а-яА-Я]+", std::wregex::icase);

        const std::wregex uk_pattern(L"[ґҐєЄїЇіІ']+", std::wregex::icase);
        const std::wregex ru_pattern(L"[ёЁъЪыЫэЭ]+", std::wregex::icase);
        const std::wregex en_pattern(L"[a-zA-Z\\[\\]\\{\\};':\\\"\\./>?,<`~]", std::wregex::icase);


        if (std::regex_search(str, cyrillic_pattern)) {
            if (std::regex_search(str, uk_pattern)) {
                return Language::UK;
            }
            if (std::regex_search(str, ru_pattern)) {
                return Language::RU;
            }
            return Language::RU;
        }
        if (std::regex_search(str, en_pattern)) {
            return Language::EN;
        }

        throw std::runtime_error("Unsupported text for translit. Allowed languages are: EN, UK, RU");
    }

    static Language detect_target_language(const std::wstring &str) {
        const std::wregex uk_pattern(L"[ґҐєЄїЇіІ']+", std::wregex::icase);
        const std::wregex ru_pattern(L"[ёЁъЪыЫэЭ]+", std::wregex::icase);
        for (const wchar_t &ch: str) {
            auto it = std::find(english_vector.begin(), english_vector.end(), ch);
            if (it == english_vector.end()) {
                continue;
            }

            const int index = std::distance(english_vector.begin(), it);

            const auto uk = std::wstring{ukrainian_vector[index]};
            const auto ru = std::wstring{russian_vector[index]};

            if (std::regex_search(ru, ru_pattern)) {
                return Language::RU;
            }

            if (std::regex_search(uk, uk_pattern)) {
                return Language::UK;
            }
        }

        return Language::RU;
    }

public:
    TranslitStringManipulator() = default;

    ~TranslitStringManipulator() override = default;


    void manipulate(std::string &str) const override {
        const auto converted_str = Encoding::utf8_to_utf16(str);

        const Language sourceLanguage = detect_source_language(converted_str);

        const Language targetLanguage = detect_target_language(converted_str);


        const std::wstring *source_alphabet = nullptr;
        const std::wstring *target_alphabet = nullptr;

        switch (sourceLanguage) {
            case Language::EN:
                source_alphabet = &english_vector;
                target_alphabet = targetLanguage == Language::UK ? &ukrainian_vector : &russian_vector;
                break;
            case Language::UK:
                source_alphabet = &ukrainian_vector;
                target_alphabet = &english_vector;
                break;
            case Language::RU:
                source_alphabet = &russian_vector;
                target_alphabet = &english_vector;
                break;
            default:
                throw std::runtime_error("Unsupported language for transliteration.");
        }

        std::wstring result;
        for (const wchar_t &ch: converted_str) {
            auto it = std::find(source_alphabet->begin(), source_alphabet->end(), ch);
            if (it != source_alphabet->end()) {
                const size_t index = std::distance(source_alphabet->begin(), it);
                const wchar_t translated_char = (*target_alphabet)[index];

                result += translated_char;
            } else {
                result += ch;
            }
        }


        str = Encoding::utf16_to_utf8(result);
    }
};

#endif
