#include "config.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <spdlog/spdlog.h>

#include <fstream>
#include <sstream>

namespace baas::configuration
{
    constexpr std::string_view seven_zip_exec = "7zipExec";
    constexpr std::string_view inputs = "inputs";
    constexpr std::string_view path = "path";
    constexpr std::string_view recursive = "recursive";
    constexpr std::string_view outputs = "outputs";


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
        // TODO What happens if this value isn't present in the json? We need to throw an exception for that
        // TODO I need a holistic solution to check for values that may not be present in the Json input. 
        config.seven_zip_exec = config_json.at(std::string(seven_zip_exec)).get<std::string>();
        if (config.seven_zip_exec.empty())
        {
            throw std::runtime_error("7zipExec value is missing in the configuration file.");
        }

        for (const auto& input : config_json.at(std::string(inputs)))
        {
            std::string input_path = input.at(std::string(path)).get<std::string>();
            bool is_recursive = input.at(std::string(recursive)).get<bool>();
            config.inputs.push_back({input_path, is_recursive});
        }

        if (config.inputs.empty())
        {
            throw BadConfiguration("No input paths found in the configuration file.");
        }

        // TODO need to implement outputs
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
            oss << "Input Path: " << input.path << "\n";
        }
        for (const auto& output : outputs)
        {
            oss << "Output Path: " << output << "\n";
        }
        logger::info(oss.str());
    }
}