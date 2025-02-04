#ifndef CAPITALAZYSTRINGMANIPULATOR_H
#define CAPITALAZYSTRINGMANIPULATOR_H
#include "Abstractions/I_StringManipulator.h"
#include "Utils/Encoding.h"
#include <sstream>
#include <vector>
#include <locale>

class CapitalizeStringManipulator final : public I_StringManipulator {
public:
    CapitalizeStringManipulator() = default;

    ~CapitalizeStringManipulator() override = default;

    void manipulate(std::string &str) const override {
        const auto converted_str = Encoding::utf8_to_utf16(str);

        std::wstringstream ss(converted_str);
        std::wstring word;
        std::vector<std::wstring> words;

        while (ss >> word) {
            if (!word.empty()) {
                word[0] = std::toupper(word[0], std::locale());
            }
            words.push_back(word);
        }

        std::wstring result;
        for (const auto &w: words) {
            result += w + L" ";
        }

        if (!result.empty() && result.back() == L' ') {
            result.pop_back();
        }

        str = Encoding::utf16_to_utf8(result);
    }
};
#endif
