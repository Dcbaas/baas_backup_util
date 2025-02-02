#include "config.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <fstream>

namespace baas::configuration
{
    constexpr std::string_view seven_zip_exec = "7zipExec";
    constexpr std::string_view inputs = "inputs";
    constexpr std::string_view path = "path";
    constexpr std::string_view recursive = "recursive";
    constexpr std::string_view outputs = "outputs";

    // Forward declaration


    Config read_config(const std::string& path)
    {
        Config config;
        json config_json;
        std::ifstream json_file(path);
        if (!json_file.is_open())
        {
            throw ConfigFileNotFound(path);
        }
        config_json = json::parse(json_file);
        config.seven_zip_exec = config_json.at(std::string(seven_zip_exec)).get<std::string>();
        for (const auto& input : config_json.at(std::string(inputs)))
        {
            std::string input_path = input.at(std::string(path)).get<std::string>();
        }

        return config;
    }
}