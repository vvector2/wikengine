#include "Common.h"

std::string ReadFile(const std::string &path) {
    std::string result;
    std::ifstream ifstream;
    ifstream.open(path);
    if (!ifstream.is_open())
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

std::vector<GLuint> GetSequenceOfConsecutiveNumbers(int n) {
    std::vector<GLuint> result;
    for (int i = 0; i < n; i++) {
        result.push_back(i);
    }
    return result;
}

void CalcBox2d(std::vector<GLfloat> &vertices, glm::vec3 &minOut, glm::vec3 &maxOut) {
    std::vector<GLfloat> x;
    std::vector<GLfloat> y;
    std::vector<GLfloat> z;

    for (int i = 0; i * 3 < vertices.size(); i++) {
        x.push_back(vertices[i * 3]);
        y.push_back(vertices[i * 3 + 1]);
        z.push_back(vertices[i * 3 + 2]);
    }

    auto maxX = std::max_element(x.begin(), x.end());
    auto minX = std::min_element(x.begin(), x.end());

    auto maxY = std::max_element(y.begin(), y.end());
    auto minY = std::min_element(y.begin(), y.end());

    auto maxZ = std::max_element(z.begin(), z.end());
    auto minZ = std::min_element(z.begin(), z.end());

    minOut.x = *minX;
    minOut.y = *minY;
    minOut.z = *minZ;

    maxOut.x = *maxX;
    maxOut.y = *maxY;
    maxOut.z = *maxZ;

}

void CalcBox2d(std::vector<GLfloat> &vertices, std::vector<GLuint> &indexes, glm::vec3 &min, glm::vec3 &max) {
    std::vector<GLfloat> vert;

    for (auto index: indexes) {
        vert.push_back(vertices[index * 3]);
        vert.push_back(vertices[index * 3 + 1]);
        vert.push_back(vertices[index * 3 + 2]);
    }

    CalcBox2d(vert, min, max);
}

std::vector<GLfloat> ScaleVerticesToBoundingBox(glm::vec3 min, glm::vec3 max, std::vector<GLfloat> &vertices) {
    std::vector<GLfloat> arr = {abs(min.x), abs(max.x), abs(min.y), abs(max.y), abs(min.z), abs(max.z)};
    auto scaleFactor = 1 / (*std::max_element(arr.begin(), arr.end()));

    std::vector<GLfloat> scaledVert;
    transform(vertices.begin(), vertices.end(), back_inserter(scaledVert),
              [scaleFactor](float x) { return x * scaleFactor; });
    return scaledVert;
}

GLfloat get_random() {
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(0, 1); // range [0, 1)
    return dis(e);
}


std::string GetFolderFromPath(const std::string &path) {
    return path.substr(0, path.find_last_of("/"));
}