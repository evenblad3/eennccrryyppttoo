#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.hpp"
#include <iostream>
#include <fstream>

int executeCryption(const std::string& taskData) {
    Task task = Task::fromString(taskData);

    ReadEnv env;
    std::string envKey = env.readEnvFile();  
    
    envKey.erase(0, envKey.find_first_not_of(" \t\n\r"));
    envKey.erase(envKey.find_last_not_of(" \t\n\r") + 1);

    int key = std::stoi(envKey);

    char ch;

    while (task.f_stream->get(ch)) {
        task.f_stream->seekp(task.f_stream->tellg() - static_cast<std::streampos>(1));

        if (task.action == Action::ENCRYPT) {
            ch = (ch + key) % 256;
        } else {
            ch = (ch - key + 256) % 256;
        }

        task.f_stream->put(ch);
    }

    return 0;
}
