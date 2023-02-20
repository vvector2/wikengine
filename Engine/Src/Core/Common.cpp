#include "Common.h"

std::string ReadFile(const std::string& path) {
    std::string result;
    std::ifstream ifstream;
    ifstream.open(path);
    if(!ifstream.is_open())
        throw std::runtime_error("Failed to open path:" + path);
    std::stringstream buffer;
    buffer << ifstream.rdbuf();
    result = buffer.str();
    ifstream.close();
    return result;
}

sole::uuid GenerateUUID() {
    return sole::uuid4();
}