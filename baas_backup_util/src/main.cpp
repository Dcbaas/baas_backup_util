#include "config.h"

#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    baas::configuration::Config config = baas::configuration::read_config("config.json");
    return 0;
}