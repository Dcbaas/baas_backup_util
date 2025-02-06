#include "argparse.h"

#include <stdexcept>

namespace baas::argparse
{
    constexpr std::string_view VERIFY_FLAG = "-v";
    constexpr std::string_view VERIFY_FLAG_LONG = "--verify";

    constexpr std::string_view config_file_flag = "-c";
    constexpr std::string_view config_file_flag_long = "--config";

    constexpr bool is_verify_flag(std::string_view arg)
    {
        return arg == VERIFY_FLAG || arg == VERIFY_FLAG_LONG;
    }

    constexpr bool is_config_file_flag(std::string_view arg)
    {
        return arg == config_file_flag || arg == config_file_flag_long;
    }

    constexpr bool is_flag(std::string_view arg)
    {
        return is_verify_flag(arg) || is_config_file_flag(arg);
    }

    enum class ConfigFileArgStatus : u_int8_t
    {
        unset,
        next_arg,
        set
    };
    // Args can either be verify or define a config file
    Arguments parse_args(std::span<char *> argv)
    {
        Arguments args{false, "baas-backup-util.json"};

        bool verify_arg_set{false};
        ConfigFileArgStatus config_file_arg_status{ConfigFileArgStatus::unset};

        for (auto arg_it = argv.begin(); arg_it != argv.end(); ++arg_it)
        {
            if (is_verify_flag(*arg_it))
            {
                if (verify_arg_set)
                {
                    throw InvalidArguments("Verify flag was decalred more than once");
                }
                else
                {
                    args.verify_config = true;
                    verify_arg_set = true;

                }
            }
            else if (is_config_file_flag(*arg_it))
            {
                if(ConfigFileArgStatus::set == config_file_arg_status)
                {
                    throw InvalidArguments("Configuration file was declared more than once");
                }
                else if (ConfigFileArgStatus::next_arg == config_file_arg_status)
                {
                    throw InvalidArguments("Configuration file flag was declared twice in a row");
                }
                else if (arg_it + 1 == argv.end() || is_flag(*(arg_it + 1)))
                {
                    throw InvalidArguments("Configuration flag was set but no path was provided");
                }
                else
                {
                    // Figure out how to set the value here
                }
            }
        }

        return args;
    }

}