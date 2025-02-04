#ifndef I_CONFIG_H
#define I_CONFIG_H
#include <nlohmann/json.hpp>

class I_Config {
    virtual void validate_json(const nlohmann::json &j) const = 0;

public:
    virtual ~I_Config() = default;

    virtual void to_json(nlohmann::json &j) const = 0;

    virtual void from_json(const nlohmann::json &j) = 0;

    [[nodiscard]] virtual std::string get_config_hash() const = 0;
};

#endif
