#ifndef READENV_HPP
#define READENV_HPP

#include <string>

class ReadEnv {
public:
    ReadEnv(const std::string& envPath = ".env");
    std::string readEnvFile() const;

private:
    std::string _envPath;
};

#endif
