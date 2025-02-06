#include "argparse.h"
#include "config.h"

#include <iostream>

int main(int argc, char* argv[]) {
    // auto config_path = "D:\\DEV\\Projects\\baas_backup_util\\docs\\example-configuration.json";
    auto args = baas::argparse::parse_args(std::span(argv, argc));

    try
    {
        baas::configuration::Config config = baas::configuration::read_config(args.config_file);
        config.display_info();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}