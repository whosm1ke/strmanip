#ifndef I_TRANSLATOR_H
#define I_TRANSLATOR_H
#include <string>
#include <future>
#include "Enums/Language.h"

class I_Translator {
protected:
    std::string api_key;
    Language source_lang;
    Language target_lang;

public:
    I_Translator(const std::string &apiKey,
                 const Language &sourceLang,
                 const Language &targetLang)
        : api_key(apiKey), source_lang(sourceLang), target_lang(targetLang) {
    }

    virtual ~I_Translator() = default;

    virtual std::future<std::string> translate_async(const std::string &text) const = 0;

    virtual std::string translate(const std::string &text) const {
        return translate_async(text).get();
    }
};
#endif
