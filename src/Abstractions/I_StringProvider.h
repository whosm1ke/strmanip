#ifndef I_STRINGPROVIDER_H
#define I_STRINGPROVIDER_H
#include <string>

class I_StringProvider {
public:
    virtual ~I_StringProvider() = default;

    [[nodiscard]] virtual std::string get_string() = 0;

    virtual void set_string(const std::string &) = 0;
};
#endif
