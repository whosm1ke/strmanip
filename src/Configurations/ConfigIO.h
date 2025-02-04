#ifndef CONFIGIO_H
#define CONFIGIO_H
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include "GlobalConfig.h"
#include "../Abstractions/I_Config.h"

template<typename Cfg>
class ConfigIO {
    static_assert(std::is_base_of_v<I_Config, Cfg>, "Cfg must derive from I_Config");

public:
    ConfigIO() = default;

    void save(const Cfg &cfg, const std::string &path) const {
        nlohmann::json j;
        cfg.to_json(j);
        std::ofstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for saving: " + path);
        }
        file << j.dump(4);
    }

    Cfg read(const std::string &path) const {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for reading: " + path);
        }

        nlohmann::json j;
        file >> j;

        Cfg cfg;
        cfg.from_json(j);
        return cfg;
    }
};


#endif
