#include "argparse.h"

#include <stdexcept>

namespace baas::argparse
{
    constexpr std::string_view VERIFY_FLAG = "-v";
    constexpr std::string_view VERIFY_FLAG_LONG = "--verify";

    constexpr std::string_view config_file_flag = "-c";
    constexpr std::string_view config_file_flag_long = "--config";

    
    // Args can either be verify or   
    Arguments parse_args(std::span<char*> argv)
    {
        for (auto arg : argv)
        {
            if (std::string(arg) == VERIFY_FLAG || std::string(arg) == VERIFY_FLAG_LONG)
            {
                return {.config_file = "", .verify_config = true};
            }
            else if (std::string(arg) == config_file_flag || std::string(arg) == config_file_flag_long)
            {
                if (argv.size() < 2)
                {
                    throw std::runtime_error("No config file provided");
                }
                return {.config_file = argv[1], .verify_config = false};
            }
        }
        Arguments args;
        return args;
    }
}