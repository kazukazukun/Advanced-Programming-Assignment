#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Open the text file
    std::ifstream file("Resources/degrees.txt");

    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Read and output the contents of the file
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    // Close the file
    file.close();

    return 0;
}