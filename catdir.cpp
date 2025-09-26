// catdir.cpp
// A program to display the contents of all files in a specified directory.
//
// Usage: catdir <directory_path>
// Options:
//   -h, --help     Display help
//   -v, --version  Show version
//
// Author: skala.skalolaz.1970@gmail.com
// Version: 1.0
// Date: 2025-06-12

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
// 
namespace fs = std::filesystem;

const std::string PROGRAM_VERSION = "1.0";

void print_help(const std::string& prog_name) {
    std::cout   << "Displays the contents of files in the specified directory.\n"
                << "Program author: skala.skalolaz.1970@gmail.com\n"
                << "Usage: " << prog_name << " <directory_path>\n"
                << "\nOptions:\n"
                << "  -h, --help     Display this help message\n"
                << "  -v, --version  Display program version\n";
}

void print_version() {
    std::cout << "catdir " << PROGRAM_VERSION << std::endl;
}


namespace fs = std::filesystem;

const std::set<std::string> allowed_extensions = {
    ".txt", ".md", ".log", ".ini", ".cfg", ".scr",
    ".cpp", ".c", "cc", "cxx", ".h", ".hpp", ".d",
    ".asm", ".s", ".S",
    ".f", ".f90", ".f95", ".f03", ".f08", ".for",
    ".py", "go", ".swift", ".kt", ".kts", ".lisp", ".lsp", ".cl", ".el",
    ".js", ".java", ".rb", ".php", ".cs", ".sh", ".bat", ".json", ".xml", ".html", ".css",
    ".yml", ".yaml"
};


const std::set<std::string> skip_extensions = {
    ".o", ".obj", ".dll", ".exe", ".bin", ".png", ".jpg", ".jpeg", ".gif", ".bmp", ".ico", ".svg", ".tif", ".tiff",
    ".pdf", ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx", ".dat", ".zip", ".rar", ".7z", ".gz", ".tar", ".mp3",
    ".mp4", ".mov", ".avi", ".mkv", ".flac", ".ogg", ".iso"
};


std::string readDataDirFiles(const std::string& directory_files) {
    std::string result;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(directory_files)) {
            if (!entry.is_regular_file())
                continue;

            auto ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

            if (ext.empty() || skip_extensions.count(ext) || allowed_extensions.count(ext) == 0)
                continue;

            std::ifstream file(entry.path());
            if (!file.is_open()) {
                std::cerr << "Error opening file: " << entry.path().filename() << std::endl;
                continue;
            }
            result += "File: " + entry.path().filename().string() + "\n\n";
            std::string line;
            while (std::getline(file, line)) {
                result += line + '\n';
            }
            result += "\n";
        }
        return "Data from files:\n" + result;
    } catch (const fs::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
        return "";
    }
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

    std::string data = readDataDirFiles(dir_path);
    std::cout << data << std::endl;

    return 0;
}
