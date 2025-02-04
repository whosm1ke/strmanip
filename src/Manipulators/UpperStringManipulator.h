#ifndef UPPERSTRINGMANIPULATOR_H
#define UPPERSTRINGMANIPULATOR_H
#include "Abstractions/I_StringManipulator.h"
#include "Utils/Encoding.h"
#include <algorithm>

class UpperStringManipulator final : public I_StringManipulator {
public:
    UpperStringManipulator() = default;

    ~UpperStringManipulator() override = default;

    void manipulate(std::string &str) const override {
        auto converted_str = Encoding::utf8_to_utf16(str);
        std::transform(converted_str.begin(), converted_str.end(), converted_str.begin(),
                       [](const wchar_t &c) { return std::toupper(c, std::locale()); });
        str = Encoding::utf16_to_utf8(converted_str);
    }
};
#endif
