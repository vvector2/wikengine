#ifndef WIKENGINE_CAMERA_H
#define WIKENGINE_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "glm/gtc/matrix_transform.hpp"

namespace Core {

    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    const float DEFAULT_YAW = -90.0f;
    const float DEFAULT_PITCH = 0.0f;
    const float DEFAULT_SPEED = 2.5f;
    const float DEFAULT_SENSITIVITY = 0.1f;
    const float DEFAULT_ZOOM = 45.0f;

    class Camera {
    public:

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = DEFAULT_YAW, float pitch = DEFAULT_PITCH);

        std::string Debug();

        glm::mat4 GetViewMatrix();

        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

        void ProcessMouseScroll(float yoffset);

        float Zoom;

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
    };

} // Core

#endif //WIKENGINE_CAMERA_H