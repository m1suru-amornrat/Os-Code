#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
 
int main() {
    fs::path dirPath = ".";  // Current directory
 
    cout << "Directory listing for: " << fs::absolute(dirPath) << endl;
    cout << string(50, '-') << endl;
 
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.is_regular_file()) {
            cout << "[FILE] " << entry.path().filename().string()
                 << "  (" << entry.file_size() << " bytes)" << endl;
        } else if (entry.is_directory()) {
            cout << "[DIR]  " << entry.path().filename().string() << "/" << endl;
        } else {
            cout << "[OTHER] " << entry.path().filename().string() << endl;
        }
    }
    return 0;
}
// Compile: g++ -std=c++17 -o dir_list dir_list.cpp
// Concepts: directory_iterator traverses one level; use
// recursive_directory_iterator for full tree traversal
