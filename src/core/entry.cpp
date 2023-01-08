#include "application/application.hpp"
#include <iostream>

static const char* logo = R""""(
--------------------------------------------------------
|  _____                     _                  .--,   |
| |  __ \                   | |             ,.-( (o)\  |
| | |__) |_ _ _ __ _ __ ___ | |_           /   .)/\ ') |
| |  ___/ _` | '__| '__/ _ \| __|       .',./'/    )/  |
| | |  | (_| | |  | | | (_) | |_     ()=///=))))==()   |
| |_|   \__,_|_|  |_|  \___/ \__|      /               |
--------------------------------------------------------
)"""";
int main() {
    std::cout << logo + 1 << std::endl;
    std::cout << "==== parrot debug console ====" << std::endl;
    intern::Application::launch();
    std::cout << "press enter to close console..." << std::flush;
    getchar();
    return EXIT_SUCCESS;
}