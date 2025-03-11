#ifndef ENCODING_H
#define ENCODING_H

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <string>
#include <codecvt>
#include <locale>

class Encoding {
public:
    static std::string utf16_to_utf8(const std::wstring &str) {
        try {
            std::wstring_convert<std::codecvt_utf8<wchar_t> > converter;
            return converter.to_bytes(str);
        } catch (const std::range_error &e) {
            throw std::runtime_error("UTF-16 to UTF-8 conversion error: " + std::string(e.what()));
        } catch (const std::exception &e) {
            throw std::runtime_error("Unexpected error during UTF-16 to UTF-8 conversion: " + std::string(e.what()));
        }
    }

    static std::wstring utf8_to_utf16(const std::string &str) {
        try {
            std::wstring_convert<std::codecvt_utf8<wchar_t> > converter;
            return converter.from_bytes(str);
        } catch (const std::range_error &e) {
            throw std::runtime_error("UTF-8 to UTF-16 conversion error: " + std::string(e.what()));
        } catch (const std::exception &e) {
            throw std::runtime_error("Unexpected error during UTF-8 to UTF-16 conversion: " + std::string(e.what()));
        }
    }

private:
    Encoding() = default;

    ~Encoding() = default;
};
#endif
