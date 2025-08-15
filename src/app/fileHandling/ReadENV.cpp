#include "ReadEnv.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

ReadEnv::ReadEnv(const std::string& envPath)
  : _envPath(envPath)
{}

std::string ReadEnv::readEnvFile() const {
    std::ifstream ifs(_envPath);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open .env file");
    }
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}
