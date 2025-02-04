#ifndef LANGUAGE_H
#define LANGUAGE_H
#include <string>
#include <stdexcept>
#include <unordered_map>

enum class Language {
    BG, // Bulgarian
    CS, // Czech
    DA, // Danish
    DE, // German
    EL, // Greek
    EN, // English
    EN_GB, // English (British)
    EN_US, // English (American)
    ES, // Spanish
    ET, // Estonian
    FI, // Finnish
    FR, // French
    HU, // Hungarian
    ID, // Indonesian
    IT, // Italian
    JA, // Japanese
    KO, // Korean
    LT, // Lithuanian
    LV, // Latvian
    NB, // Norwegian (Bokmål)
    NL, // Dutch
    PL, // Polish
    PT, // Portuguese
    PT_BR, // Portuguese (Brazilian)
    PT_PT, // Portuguese (European)
    RO, // Romanian
    RU, // Russian
    SK, // Slovak
    SL, // Slovenian
    SV, // Swedish
    TR, // Turkish
    UK, // Ukrainian
    ZH, // Chinese
    ZH_HANS, // Chinese (Simplified)
    ZH_HANT, // Chinese (Traditional)
    UNKNOWN // Unknown
};

static const std::unordered_map<Language, std::string> LanguageToString{
    {Language::BG, "BG"}, {Language::CS, "CS"}, {Language::DA, "DA"},
    {Language::DE, "DE"}, {Language::EL, "EL"}, {Language::EN, "EN"},
    {Language::EN_GB, "EN-GB"}, {Language::EN_US, "EN-US"}, {Language::ES, "ES"},
    {Language::ET, "ET"}, {Language::FI, "FI"}, {Language::FR, "FR"},
    {Language::HU, "HU"}, {Language::ID, "ID"}, {Language::IT, "IT"},
    {Language::JA, "JA"}, {Language::KO, "KO"}, {Language::LT, "LT"},
    {Language::LV, "LV"}, {Language::NB, "NB"}, {Language::NL, "NL"},
    {Language::PL, "PL"}, {Language::PT, "PT"}, {Language::PT_BR, "PT-BR"},
    {Language::PT_PT, "PT-PT"}, {Language::RO, "RO"}, {Language::RU, "RU"},
    {Language::SK, "SK"}, {Language::SL, "SL"}, {Language::SV, "SV"},
    {Language::TR, "TR"}, {Language::UK, "UK"}, {Language::ZH, "ZH"},
    {Language::ZH_HANS, "ZH-HANS"}, {Language::ZH_HANT, "ZH-HANT"},
    {Language::UNKNOWN, "UNKNOWN"}
};

static const std::unordered_map<std::string, Language> StringToLanguage{
    {"BG", Language::BG}, {"CS", Language::CS}, {"DA", Language::DA},
    {"DE", Language::DE}, {"EL", Language::EL}, {"EN", Language::EN},
    {"EN-GB", Language::EN_GB}, {"EN-US", Language::EN_US}, {"ES", Language::ES},
    {"ET", Language::ET}, {"FI", Language::FI}, {"FR", Language::FR},
    {"HU", Language::HU}, {"ID", Language::ID}, {"IT", Language::IT},
    {"JA", Language::JA}, {"KO", Language::KO}, {"LT", Language::LT},
    {"LV", Language::LV}, {"NB", Language::NB}, {"NL", Language::NL},
    {"PL", Language::PL}, {"PT", Language::PT}, {"PT-BR", Language::PT_BR},
    {"PT-PT", Language::PT_PT}, {"RO", Language::RO}, {"RU", Language::RU},
    {"SK", Language::SK}, {"SL", Language::SL}, {"SV", Language::SV},
    {"TR", Language::TR}, {"UK", Language::UK}, {"ZH", Language::ZH},
    {"ZH-HANS", Language::ZH_HANS}, {"ZH-HANT", Language::ZH_HANT},
    {"UNKNOWN", Language::UNKNOWN}
};

static std::string language_to_string(const Language lang) {
    if (const auto it = LanguageToString.find(lang); it != LanguageToString.end() && it->second != "UNKNOWN") {
        return it->second;
    }
    throw std::invalid_argument("Unsupported language code");
}


static Language string_to_language(const std::string &str) {
    if (const auto it = StringToLanguage.find(str); it != StringToLanguage.end() && it->second != Language::UNKNOWN) {
        return it->second;
    }
    throw std::invalid_argument("Unsupported language code: " + str);
}

static bool operator==(const Language lhs, const std::string &rhs) {
    return language_to_string(lhs) == rhs;
}

static bool operator!=(const Language lhs, const std::string &rhs) {
    return !(lhs == rhs);
}
#endif
