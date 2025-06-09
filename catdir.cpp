// catdir.cpp
// A program to display the contents of all files in a specified directory.
//
// Usage: catdir <directory_path>
// Options:
//   -h, --help     Display help
//   -v, --version  Show version
//
// Author: skala.skalolaz.1970@gmail.com
// Version: 0.9.1
// Date: 2025-06-09

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

const std::string PROGRAM_VERSION = "0.9.1";

void print_help(const std::string& prog_name) {
    std::cout << "Usage: " << prog_name << " <directory_path>\n"
              << "Displays the contents of all files in the specified directory.\n"
              << "\nOptions:\n"
              << "  -h, --help     Display this help message\n"
              << "  -v, --version  Display program version\n";
}

void print_version() {
    std::cout << "Program version: " << PROGRAM_VERSION << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory_path>\n"
                  << "Try '" << argv[0] << " --help' for more information.\n";
        return 1;
    }
    
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
        print_help(argv[0]);
        return 0;
    }
    if (arg == "-v" || arg == "--version") {
        print_version();
        return 0;
    }

    std::string dir_path = arg;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(dir_path)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                std::ifstream file(entry.path());

                if (!file.is_open()) {
                    std::cerr << "Error opening file: " << filename << std::endl;
                    continue;
                }

                std::cout << "File: " << filename << "\n\n";

                std::string line;
                while (std::getline(file, line)) {
                    std::cout << line << '\n';
                }
                std::cout << "\n";
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
