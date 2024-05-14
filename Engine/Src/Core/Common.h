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
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <reactphysics3d/reactphysics3d.h>


std::string ReadFile(const std::string &path);

template<typename T>
std::vector<T> Filter(std::vector<T> arr, std::function<bool(T)> pred) {
    std::vector<T> result;
    std::copy_if(arr.begin(), arr.end(), std::back_inserter(result), pred);
    return result;
}

sole::uuid GenerateUUID();

std::vector<GLuint> GetSequenceOfConsecutiveNumbers(int n);

void CalcBox2d(std::vector<GLfloat> &vertices, glm::vec3 &min, glm::vec3 &max);

void CalcBox2d(std::vector<GLfloat> &vertices, std::vector<GLuint> &indexes, glm::vec3 &min, glm::vec3 &max);

std::vector<GLfloat> ScaleVerticesToBoundingBox(glm::vec3 min, glm::vec3 max, std::vector<GLfloat> &vertices);

class NotImplemented : public std::logic_error {
public:
    NotImplemented() : std::logic_error("Function not yet implemented") {};
};

GLfloat get_random();

std::string GetFolderFromPath(const std::string &path);

void printMat(glm::mat4 mat);

glm::mat4 ReactTransformToMat(reactphysics3d::Transform transform);

reactphysics3d::Transform MatToReactTransform(glm::mat4 mat);

reactphysics3d::Vector3 ToReactVec3(glm::vec3 v);

template<typename T>
T Max(T a, T b) {
    return a > b ? a : b;
}

#endif //WIKENGINE_COMMON_H

