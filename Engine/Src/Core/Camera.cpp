#include "Camera.h"

namespace Core {
    Camera::Camera(glm::vec3 position, glm::vec3 up,
                   float yaw, float pitch) : Zoom(DEFAULT_ZOOM),
                                            front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                            movementSpeed(DEFAULT_SPEED), mouseSensitivity(DEFAULT_SENSITIVITY) {
        this->pos = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();
    }

    std::string Camera::Debug() {
        char buff[100];
        snprintf(buff, sizeof(buff), "Camera position (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
        std::string buffAsStdStr = buff;
        return buffAsStdStr;
    }

    glm::mat4 Camera::GetViewMatrix() {
        return glm::lookAt(pos, pos + front, Up);
    }

    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        float velocity = movementSpeed * deltaTime;
        if (direction == FORWARD)
            pos += front * velocity;
        if (direction == BACKWARD)
            pos -= front * velocity;
        if (direction == LEFT)
            pos -= right * velocity;
        if (direction == RIGHT)
            pos += right * velocity;

    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch) {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();

    }

    void Camera::ProcessMouseScroll(float yoffset) {
        Zoom -= (float) yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    float Zoom;

    void Camera::updateCameraVectors() {
        // calculate the new Front vector
        glm::vec3 updatedFront;
        updatedFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        updatedFront.y = sin(glm::radians(pitch));
        updatedFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(updatedFront);
        // also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(front,
                                          worldUp));
        // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(right, front));
    }

} // core