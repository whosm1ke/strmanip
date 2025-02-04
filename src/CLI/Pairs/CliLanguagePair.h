#ifndef CLILANGUAGEPAIR_H
#define CLILANGUAGEPAIR_H
#include <string>
#include "CliPair.h"
#include "Enums/Language.h"
#include <stdexcept>

class CliLanguagePair final : public CliPair<Language> {
public:
    explicit CliLanguagePair(const std::string &arg) {
        parse(arg);
    }

    void parse(const std::string &arg) override {
        const size_t pos = arg.find(" ");

        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid argument format. Add space or provide value in format --name value");
        }

        name = arg.substr(0, pos);
        const std::string lang_str = arg.substr(pos + 1);

        value = string_to_language(lang_str);
    }
};

#endif
