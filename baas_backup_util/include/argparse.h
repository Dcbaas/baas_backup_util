#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <string>
#include <span>

namespace baas::argparse
{
    struct Arguments
    {
        bool verify_config;
        std::string config_file;
    };

    Arguments parse_args(std::span<char*> argv);

    class InvalidArguments : public std::exception
    {
    public:
        explicit InvalidArguments(const std::string& message) : message_(message) {}

        const char* what() const noexcept override
        {
            return message_.c_str();
        }

    private:
        std::string message_;
    };
}
#endif // ARGPARSE_H