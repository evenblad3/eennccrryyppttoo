#ifndef TASK_HPP
#define TASK_HPP

#include "../fileHandling/IO.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>

enum class Action {
    ENCRYPT,
    DECRYPT
};

struct Task {
    std::string filePath;
    std::unique_ptr<std::fstream> f_stream;
    Action action;

    Task(std::unique_ptr<std::fstream> stream, Action act, std::string filePath) 
        : filePath(filePath), f_stream(std::move(stream)), action(act) {}
        
    std::string toString() const {
        std::ostringstream oss;
        oss << filePath << "," << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");
        return oss.str();
    }

    static Task fromString(const std::string& taskData) {
        std::istringstream iss(taskData);
        std::string filePath, actionStr;

        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr)) {
            Action action = (actionStr == "ENCRYPT") ? Action::ENCRYPT : Action::DECRYPT;
            
            IO io(filePath);
            auto f_stream = std::make_unique<std::fstream>(std::move(io.getFileStream()));

            if (!f_stream || !f_stream->is_open()) {
                throw std::runtime_error("Failed to open file: " + filePath);
            }

            return Task(std::move(f_stream), action, std::move(filePath));
        } else {
            throw std::runtime_error("Invalid task data format");
        }
    }
};

#endif
