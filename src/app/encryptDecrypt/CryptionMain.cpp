#include <iostream>
#include <string>
#include "Cryption.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./cryption <task_data>" << std::endl;
        return 1;
    }

    try {
        std::string taskData(argv[1]);
        executeCryption(taskData);
        std::cout << "Cryption operation completed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
