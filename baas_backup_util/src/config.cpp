#include "config.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <spdlog/spdlog.h>

#include <concepts>
#include <optional>
#include <fstream>
#include <sstream>

namespace baas::configuration
{
    constexpr std::string_view seven_zip_exec = "7zipExec";
    constexpr std::string_view inputs = "inputs";
    constexpr std::string_view path = "path";
    constexpr std::string_view recursive = "recursive";
    constexpr std::string_view outputs = "outputs";

    template <typename T>
    concept ExceptionType = std::derived_from<T, std::exception>;

    template <typename T, ExceptionType E>
    T get_or_throw(const json& j, const std::string& key, const E& exception)
    {
        if (j.contains(key))
        {
            return j.at(key).get<T>();
        }
        throw exception;
    }


    Config read_config(const std::string& file_path)
    {
        Config config;
        json config_json;
        std::ifstream json_file(file_path);
        if (!json_file.is_open())
        {
            throw ConfigFileNotFound(file_path);
        }
        config_json = json::parse(json_file);

        config.seven_zip_exec = get_or_throw<std::string>(config_json, 
            std::string(seven_zip_exec), 
            BadConfiguration("7zipExec value is missing in the configuration file.")
        );

        if (!config_json.contains(std::string(inputs)))
        {
            throw BadConfiguration("No input paths found in the configuration file.");
        }

        for (const auto& input : config_json.at(std::string(inputs)))
        {
            // std::string input_path = input.at(std::string(path)).get<std::string>();
            std::string input_path = get_or_throw<std::string>(input, 
                std::string(path), 
                BadConfiguration("Input list contains entry where path is missing.")
            );
            bool is_recursive{false};
            if (input.contains(std::string(recursive)))
            {
                is_recursive = input.at(std::string(recursive)).get<bool>();
            }
            config.inputs.push_back({input_path, is_recursive});
        }


        // Is this redundant? Probably
        if (config.inputs.empty())
        {
            throw BadConfiguration("No input paths found in the configuration file.");
        }

        // TODO need to implement outputs
        if (!config_json.contains(std::string(outputs)))
        {
            throw BadConfiguration("No output paths found in the configuration file.");
        }

        for (const auto& output : config_json.at(std::string(outputs)))
        {
            config.outputs.push_back(output.get<std::string>());
        }

        if (config.outputs.empty())
        {
            throw BadConfiguration("No output paths found in the configuration file.");
        }

        return config;
    }


    void Config::display_info() const
    {
        namespace logger = spdlog;
        std::ostringstream oss;
        oss << "7zip Executable: " << seven_zip_exec << "\n";
        for (const auto& input : inputs)
        {
            oss << '\t' << "Input Path: " << input.path << "\n";
        }
        for (const auto& output : outputs)
        {
            oss << '\t' << "Output Path: " << output << "\n";
        }
        logger::info(oss.str());
    }
}