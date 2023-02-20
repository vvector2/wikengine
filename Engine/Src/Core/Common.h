//
// Created by wiktor on 15.01.23.
//

#ifndef WIKENGINE_COMMON_H
#define WIKENGINE_COMMON_H

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../../../external/sole/sole.hpp"

std::string ReadFile(const std::string& path);

template <typename T>
std::vector<T> Filter(std::vector<T> arr, std::function<bool(T)> pred){
    std::vector<T> result;
    std::copy_if (arr.begin(), arr.end(), std::back_inserter(result), pred );
    return result;
}

sole::uuid GenerateUUID();

class NotImplemented : public std::logic_error
{
public:
    NotImplemented() : std::logic_error("Function not yet implemented") { };
};

#endif //WIKENGINE_COMMON_H
