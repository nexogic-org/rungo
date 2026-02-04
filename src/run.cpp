#include "run.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <vector>

namespace fs = std::filesystem;

// Simple helper to find a value in a JSON-like string
// This is not a full JSON parser, but enough for the current project.json structure
std::string extract_json_value(const std::string& content, const std::string& key, const std::string& parent_key = "") {
    size_t start_search = 0;
    
    // If a parent key is provided (e.g., "compiler"), find it first
    if (!parent_key.empty()) {
        size_t parent_pos = content.find("\"" + parent_key + "\"");
        if (parent_pos == std::string::npos) return "";
        start_search = content.find("{", parent_pos);
        if (start_search == std::string::npos) return "";
    }

    size_t key_pos = content.find("\"" + key + "\"", start_search);
    if (key_pos == std::string::npos) return "";

    size_t colon_pos = content.find(":", key_pos);
    if (colon_pos == std::string::npos) return "";

    size_t quote_start = content.find("\"", colon_pos);
    if (quote_start == std::string::npos) return "";

    size_t quote_end = content.find("\"", quote_start + 1);
    if (quote_end == std::string::npos) return "";

    return content.substr(quote_start + 1, quote_end - quote_start - 1);
}

void run_project() {
    fs::path project_config_path = "project.json";

    if (!fs::exists(project_config_path)) {
        std::cerr << "Error: 'project.json' not found. This does not appear to be a valid Korelin project." << std::endl;
        return;
    }

    std::ifstream config_file(project_config_path);
    if (!config_file.is_open()) {
        std::cerr << "Error: Unable to open 'project.json'." << std::endl;
        return;
    }

    std::string content((std::istreambuf_iterator<char>(config_file)), std::istreambuf_iterator<char>());
    config_file.close();

    // Extract compiler.main
    std::string main_file = extract_json_value(content, "main", "compiler");

    if (main_file.empty()) {
        // Fallback or error? Let's try to find "main" without parent if "compiler" block logic failed, 
        // but strict adherence to structure is better.
        // If empty, it might be that the user didn't define it or our simple parser failed.
        std::cerr << "Error: Could not find 'compiler.main' in project.json." << std::endl;
        return;
    }

    // Construct command: korelin run <main_file> -lib project.json>requirement
    std::string command = "korelin run " + main_file + " -lib project.json>requirement";

    std::cout << "Executing: " << command << std::endl;
    
    int result = std::system(command.c_str());
    
    if (result != 0) {
        // std::cerr << "Command failed with exit code: " << result << std::endl;
        // system() returns implementation-defined value, usually status of child
    }
}
