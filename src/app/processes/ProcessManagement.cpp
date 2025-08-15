#include <iostream>
#include "ProcessManagement.hpp"
#include "Task.hpp"
#include <queue>
#include <memory>
#include <cstring>
#include "../encryptDecrypt/Cryption.hpp"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/wait.h>
#endif

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    if (task) {
        taskQueue.push(std::move(task));
        return true;
    }
    return false;
}

void ProcessManagement::executeTasks() {
    while (!taskQueue.empty()) {
        std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
        taskQueue.pop();
        
        std::cout << "Executing task: " << taskToExecute->toString() << std::endl;

        executeCryption(taskToExecute->toString());
    }
}
