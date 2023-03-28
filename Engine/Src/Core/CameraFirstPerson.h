#ifndef WIKENGINE_CAMERAFIRSTPERSON_H
#define WIKENGINE_CAMERAFIRSTPERSON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "glm/gtc/matrix_transform.hpp"

const float DEFAULT_YAW = -90.0f;
const float DEFAULT_PITCH = 0.0f;
const float DEFAULT_SPEED = 1.0f;
const float DEFAULT_SENSITIVITY = 0.05f;
const float DEFAULT_ZOOM = 45.0f;

class CameraFirstPerson {
public:
    CameraFirstPerson(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                      float yaw = DEFAULT_YAW, float pitch = DEFAULT_PITCH);
    std::string Debug() const;
    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(glm::vec2 dir, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    inline float Zoom() const {return zoom;}
    inline void SetZoom(float _zoom) {zoom = _zoom;}
private:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 Up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;

    void updateCameraVectors();

    float zoom;
};


#endif //WIKENGINE_CAMERAFIRSTPERSON_H
