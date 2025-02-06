#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <string>
#include <span>

namespace baas::argparse
{
    struct Arguments
    {
        std::string config_file;
        bool verify_config;
    };

    Arguments parse_args(std::span<char*> argv);
}
#endif // ARGPARSE_H