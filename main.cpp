#include <iostream>
#include <filesystem>
#include <memory>
#include <fstream>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"
using namespace std;
namespace fs = filesystem;

int main(int argc, char* argv[]) {
    string directory, action;
    
    cout << "Enter the directory path: ";
    getline(cin, directory);
    cout << "Enter the action (encrypt/decrypt): ";
    getline(cin, action);

    try {
        if (!fs::exists(directory) || !fs::is_directory(directory)) {
            cerr << "Error: Invalid directory path!" << endl;
            return 1;
        }
        
        if (fs::is_empty(directory)) {
            cerr << "Warning: The directory is empty!" << endl;
        }

        ProcessManagement processManagement;

        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                string filePath = entry.path().string();

                unique_ptr<fstream> fileStream = 
                    make_unique<fstream>(filePath, ios::in | ios::out | ios::binary);

                if (!fileStream->is_open()) {
                    cerr << "Error: Unable to open file due to permission issues: " << filePath << endl;
                    continue;
                }

                Action taskAction = (action == "encrypt") ? Action::ENCRYPT : Action::DECRYPT;
                auto task = make_unique<Task>(move(fileStream), taskAction, filePath);
                processManagement.submitToQueue(move(task));
            }
        }

        processManagement.executeTasks();
    } catch (const fs::filesystem_error& ex) {
        cerr << "Filesystem error: " << ex.what() << endl;
    } catch (const exception& ex) {
        cerr << "General error: " << ex.what() << endl;
    }

    return 0;
}
