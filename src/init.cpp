#include "init.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <iomanip>
#include "resources.hpp"

namespace fs = std::filesystem;

const std::string MIN_KORELIN_VERSION = "1.0.0";
const std::string DEFAULT_KORELIN_VERSION = "1.0.0";
const std::string DEFAULT_PROJECT_VERSION = "0.1.0";

std::string get_current_date() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y / %m / %d");
    return oss.str();
}

void create_default_project(const fs::path& project_path, const std::string& project_name, const std::string& korelin_version, const std::string& project_version) {
    // Create directories
    fs::create_directories(project_path / "src");
    fs::create_directories(project_path / "bin");
    fs::create_directories(project_path / "rungo_modules");

    // Create rungo_modules/package.rungo
    std::ofstream package_rungo(project_path / "rungo_modules" / "package.rungo");
    if (package_rungo.is_open()) {
        package_rungo << "Korelin>=" << MIN_KORELIN_VERSION << "\n";
        package_rungo.close();
    } else {
            std::cerr << "Failed to create rungo_modules/package.rungo" << std::endl;
    }

    // Create project.json
    std::ofstream project_json(project_path / "project.json");
    if (project_json.is_open()) {
        project_json << "{\n"
                        << "    \"name\": \"" << project_name << "\",\n"
                        << "    \"version\": \"" << (project_version.empty() ? DEFAULT_PROJECT_VERSION : project_version) << "\",\n"
                        << "    \"introduction\": {\n"
                        << "        \"auther\": {\n"
                        << "            \"name\": \"\",\n"
                        << "            \"email\": \"\",\n"
                        << "            \"github\": \"\",\n"
                        << "            \"blog\": \"\"\n"
                        << "        }\n"
                        << "    },\n"
                        << "    \"type\": \"project\",\n"
                        << "    \"license\": \"\",\n"
                        << "    \"description\": \"\",\n"
                        << "    \"requirement\": {},\n"
                        << "    \"doc\": \"\",\n"
                        << "    \"compiler\": {\n"
                        << "        \"main\": \"src/main.kri\",\n"
                        << "        \"bin\": \"./bin/\"\n"
                        << "    },\n"
                        << "    \"url\": \"\"\n"
                        << "}";
        project_json.close();
    } else {
        std::cerr << "Failed to create project.json" << std::endl;
        return;
    }

    // Create src/main.kri
    std::ofstream main_kri(project_path / "src" / "main.kri");
    if (main_kri.is_open()) {
        main_kri << "// " << get_current_date() << " Rungo 一个常量版本\n"
                    << "import os.print;\n\n"
                    << "void main() {\n"
                    << "    print(\"Hello World\\n\");\n"
                    << "}\n";
        main_kri.close();
    } else {
        std::cerr << "Failed to create src/main.kri" << std::endl;
    }
}

void create_plugin_project(const fs::path& project_path, const std::string& project_name, const std::string& korelin_version, const std::string& project_version) {
    // Create directories
    fs::create_directories(project_path / "rungo_modules");
    // Plugin usually might have an 'out' directory or similar if specified in project.json "bin": "./out/"
    // But for source structure, just root and rungo_modules seem present in the example.
    // I will create 'out' directory just in case since project.json mentions it.
    fs::create_directories(project_path / "out");

    // Create rungo_modules/package.rungo
    std::ofstream package_rungo(project_path / "rungo_modules" / "package.rungo");
    if (package_rungo.is_open()) {
        package_rungo << "Korelin>=" << MIN_KORELIN_VERSION << "\n";
        package_rungo.close();
    } else {
            std::cerr << "Failed to create rungo_modules/package.rungo" << std::endl;
    }

    // Create project.json
    std::ofstream project_json(project_path / "project.json");
    if (project_json.is_open()) {
        project_json << "{\n"
                        << "    \"name\": \"" << project_name << "\",\n"
                        << "    \"version\": \"" << (project_version.empty() ? DEFAULT_PROJECT_VERSION : project_version) << "\",\n"
                        << "    \"introduction\": {\n"
                        << "        \"auther\": {\n"
                        << "            \"name\": \"\",\n"
                        << "            \"email\": \"\",\n"
                        << "            \"github\": \"\",\n"
                        << "            \"blog\": \"\"\n"
                        << "        }\n"
                        << "    },\n"
                        << "    \"type\": \"plugin\",\n"
                        << "    \"license\": \"\",\n"
                        << "    \"description\": \"\",\n"
                        << "    \"requirement\": {},\n"
                        << "    \"doc\": \"\",\n"
                        << "    \"compiler\": {\n"
                        << "        \"main\": \"main.kri\",\n"
                        << "        \"bin\": \"./out/\"\n"
                        << "    },\n"
                        << "    \"url\": \"\"\n"
                        << "}";
        project_json.close();
    } else {
        std::cerr << "Failed to create project.json" << std::endl;
        return;
    }

    // Create main.kri
    std::ofstream main_kri(project_path / "main.kri");
    if (main_kri.is_open()) {
        main_kri << "import plugin;\n"
                 << "void main() {plugin.print_hello();}\n";
        main_kri.close();
    } else {
        std::cerr << "Failed to create main.kri" << std::endl;
    }

    // Create plugin.kri
    std::ofstream plugin_kri(project_path / "plugin.kri");
    if (plugin_kri.is_open()) {
        plugin_kri << "import os;\n"
                   << "void print_hello() {\n"
                   << "    os.println(\"hello Korelin Plugin\");\n"
                   << "}\n";
        plugin_kri.close();
    } else {
        std::cerr << "Failed to create plugin.kri" << std::endl;
    }
}

void create_framework_project(const fs::path& project_path, const std::string& project_name, const std::string& korelin_version, const std::string& project_version) {
    // Create directories
    fs::create_directories(project_path / "rungo_modules");
    fs::create_directories(project_path / "out");

    // Create rungo_modules/package.rungo
    std::ofstream package_rungo(project_path / "rungo_modules" / "package.rungo");
    if (package_rungo.is_open()) {
        package_rungo << "Korelin>=" << MIN_KORELIN_VERSION << "\n";
        package_rungo.close();
    } else {
            std::cerr << "Failed to create rungo_modules/package.rungo" << std::endl;
    }

    // Create project.json
    std::ofstream project_json(project_path / "project.json");
    if (project_json.is_open()) {
        project_json << "{\n"
                        << "    \"name\": \"" << project_name << "\",\n"
                        << "    \"version\": \"" << (project_version.empty() ? DEFAULT_PROJECT_VERSION : project_version) << "\",\n"
                        << "    \"introduction\": {\n"
                        << "        \"auther\": {\n"
                        << "            \"name\": \"\",\n"
                        << "            \"email\": \"\",\n"
                        << "            \"github\": \"\",\n"
                        << "            \"blog\": \"\"\n"
                        << "        }\n"
                        << "    },\n"
                        << "    \"type\": \"framework\",\n"
                        << "    \"license\": \"\",\n"
                        << "    \"description\": \"\",\n"
                        << "    \"requirement\": {},\n"
                        << "    \"doc\": \"\",\n"
                        << "    \"compiler\": {\n"
                        << "        \"main\": \"main.kri\",\n"
                        << "        \"bin\": \"./out/\"\n"
                        << "    },\n"
                        << "    \"url\": \"\"\n"
                        << "}";
        project_json.close();
    } else {
        std::cerr << "Failed to create project.json" << std::endl;
        return;
    }

    // Create main.kri
    std::ofstream main_kri(project_path / "main.kri");
    if (main_kri.is_open()) {
        main_kri << "import framework;\n"
                 << "void main() {framework.print_hello();}\n";
        main_kri.close();
    } else {
        std::cerr << "Failed to create main.kri" << std::endl;
    }

    // Create framework.kri
    std::ofstream framework_kri(project_path / "framework.kri");
    if (framework_kri.is_open()) {
        framework_kri << "import os;\n"
                      << "void print_hello() {\n"
                      << "    os.println(\"hello Korelin Framework\");\n"
                      << "}\n";
        framework_kri.close();
    } else {
        std::cerr << "Failed to create framework.kri" << std::endl;
    }
}

void create_cplugin_project(const fs::path& project_path, const std::string& project_name, const std::string& korelin_version, const std::string& project_version) {
    // Create directories
    fs::create_directories(project_path / "rungo_modules" / "c");
    fs::create_directories(project_path / "out");

    // Create rungo_modules/package.rungo
    std::ofstream package_rungo(project_path / "rungo_modules" / "package.rungo");
    if (package_rungo.is_open()) {
        package_rungo << "korelin>=" << (korelin_version.empty() ? DEFAULT_KORELIN_VERSION : korelin_version) << "\n"
                      << "c==11\n";
        package_rungo.close();
    } else {
            std::cerr << "Failed to create rungo_modules/package.rungo" << std::endl;
    }

    // Create project.json
    std::ofstream project_json(project_path / "project.json");
    if (project_json.is_open()) {
        project_json << "{\n"
                        << "    \"name\": \"" << project_name << "\",\n"
                        << "    \"version\": \"" << (project_version.empty() ? DEFAULT_PROJECT_VERSION : project_version) << "\",\n"
                        << "    \"introduction\": {\n"
                        << "        \"auther\": {\n"
                        << "            \"name\": \"\",\n"
                        << "            \"email\": \"\",\n"
                        << "            \"github\": \"\",\n"
                        << "            \"blog\": \"\"\n"
                        << "        }\n"
                        << "    },\n"
                        << "    \"type\": \"cplugin\",\n"
                        << "    \"license\": \"\",\n"
                        << "    \"description\": \"\",\n"
                        << "    \"requirement\": {},\n"
                        << "    \"doc\": \"\",\n"
                        << "    \"compiler\": {\n"
                        << "        \"main\": \"main.kri\",\n"
                        << "        \"bin\": \"./out/\"\n"
                        << "    },\n"
                        << "    \"url\": \"\"\n"
                        << "}";
        project_json.close();
    } else {
        std::cerr << "Failed to create project.json" << std::endl;
        return;
    }

    // Create main.kri
    std::ofstream main_kri(project_path / "main.kri");
    if (main_kri.is_open()) {
        main_kri << "import os;\n"
                 << "void main() {\n"
                 << "    os.print(\"hello world\");\n"
                 << "}\n";
        main_kri.close();
    } else {
        std::cerr << "Failed to create main.kri" << std::endl;
    }

    // Create main.c
    std::ofstream main_c(project_path / "main.c");
    if (main_c.is_open()) {
        // Empty file as per reference
        main_c.close();
    } else {
        std::cerr << "Failed to create main.c" << std::endl;
    }

    // Write embedded gcc.exe and g++.exe
    try {
        fs::path dest_dir = project_path / "rungo_modules" / "c";
        
        // Write gcc.exe
        std::ofstream gcc_out(dest_dir / "gcc.exe", std::ios::binary);
        if (gcc_out) {
            gcc_out.write(reinterpret_cast<const char*>(gcc_exe_data), gcc_exe_data_len);
        } else {
            std::cerr << "Failed to write gcc.exe" << std::endl;
        }

        // Write g++.exe
        std::ofstream gpp_out(dest_dir / "g++.exe", std::ios::binary);
        if (gpp_out) {
            gpp_out.write(reinterpret_cast<const char*>(gpp_exe_data), gpp_exe_data_len);
        } else {
            std::cerr << "Failed to write g++.exe" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error writing compiler executables: " << e.what() << std::endl;
    }
}

void init_project(const std::string& project_name, const std::string& template_name, const std::string& korelin_version, const std::string& project_version) {
    fs::path project_path = project_name;
    
    std::string actual_version = korelin_version.empty() ? DEFAULT_KORELIN_VERSION : korelin_version;

    if (fs::exists(project_path)) {
        std::cout << "Error: Directory '" << project_name << "' already exists." << std::endl;
        return;
    }

    try {
        if (template_name == "plugin") {
            create_plugin_project(project_path, project_name, actual_version, project_version);
        } else if (template_name == "fw") {
            create_framework_project(project_path, project_name, actual_version, project_version);
        } else if (template_name == "cplugin") {
            create_cplugin_project(project_path, project_name, actual_version, project_version);
        } else {
            if (!template_name.empty()) {
                std::cout << "Error: Invalid template parameter '" << template_name << "'" << std::endl;
                return;
            }
            create_default_project(project_path, project_name, actual_version, project_version);
        }

        std::string created_type = "empty Korelin";
        if (template_name == "plugin") created_type = "plugin";
        else if (template_name == "fw") created_type = "framework";
        else if (template_name == "cplugin") created_type = "cplugin";

        std::cout << "Initialized " << created_type << " project in " << fs::absolute(project_path).string() << std::endl;

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}
