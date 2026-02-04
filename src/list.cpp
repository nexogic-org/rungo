#include "list.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void list_packages() {
    fs::path modules_path = "rungo_modules";
    fs::path package_config = modules_path / "package.rungo";

    if (!fs::exists(modules_path) || !fs::exists(package_config)) {
        std::cerr << "Error: This directory does not appear to be a valid Korelin project." << std::endl;
        std::cerr << "Missing 'rungo_modules' directory or 'package.rungo' file." << std::endl;
        return;
    }

    std::cout << "Installed packages:" << std::endl;
    bool found_any = false;

    try {
        for (const auto& entry : fs::directory_iterator(modules_path)) {
            if (entry.is_directory()) {
                std::cout << " - " << entry.path().filename().string() << std::endl;
                found_any = true;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return;
    }

    if (!found_any) {
        std::cout << " (No packages installed)" << std::endl;
    }
}
