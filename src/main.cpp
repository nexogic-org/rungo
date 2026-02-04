#include <iostream>
#include <string>
#include "help.hpp"
#include "init.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 0;
    }

    std::string command = argv[1];

    if (command == "init") {
        if (argc < 3) {
            std::cout << "Usage: rungo init <project-name>" << std::endl;
            return 1;
        }
        init_project(argv[2]);
    } else if (command == "install" || command == "uninstall" || command == "list") {
        std::cout << "Command '" << command << "' is not yet implemented." << std::endl;
    } else {
        std::cout << "Unknown command: " << command << std::endl;
        print_help();
    }

    return 0;
}
