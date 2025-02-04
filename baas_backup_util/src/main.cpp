#include "config.h"

#include <iostream>

int main(int argc, char* argv[]) {
    auto config_path = "D:\\DEV\\Projects\\baas_backup_util\\docs\\example-configuration.json";
    try
    {
        baas::configuration::Config config = baas::configuration::read_config(config_path);
        config.display_info();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}