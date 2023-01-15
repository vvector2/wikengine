#include "Common.h"

std::string ReadFile(const std::string& path) {
    std::string vertexShaderCode;
    std::ifstream ifstream;
    try {
        ifstream.open(path);
        std::stringstream buffer;
        buffer << ifstream.rdbuf();
        vertexShaderCode = buffer.str();
    } catch(...) {
        if (ifstream.is_open())
            ifstream.close();
    };
    if (ifstream.is_open())
        ifstream.close();
    return vertexShaderCode;
}