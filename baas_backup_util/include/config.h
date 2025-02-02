#include <string>
#include <vector>
#include <exception>

namespace baas::configuration
{
    struct Config
    {
        struct Input
        {
            std::string path;
            bool recursive;
        };
        std::string seven_zip_exec;
        std::vector<Input> inputs;
        std::vector<std::string> outputs;
    };

    Config read_config(const std::string& path);

    class ConfigFileNotFound : public std::exception
    {
    public:
        ConfigFileNotFound(const std::string& file_path)
            : message("Configuration file not found: " + file_path) {}

        virtual const char* what() const noexcept override
        {
            return message.c_str();
        }

    private:
        std::string message;
    };
}