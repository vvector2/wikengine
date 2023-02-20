#include "CameraFirstPerson.h"

CameraFirstPerson::CameraFirstPerson(glm::vec3 position, glm::vec3 up,
                                     float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                        movementSpeed(DEFAULT_SPEED),
                                        mouseSensitivity(DEFAULT_SENSITIVITY), zoom(DEFAULT_ZOOM) {
    this->pos = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

std::string CameraFirstPerson::Debug() const {
    char buff[100];
    snprintf(buff, sizeof(buff), "Camera position (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
    std::string buffAsStdStr = buff;
    return buffAsStdStr;
}

glm::mat4 CameraFirstPerson::GetViewMatrix() {
    return glm::lookAt(pos, pos + front, Up);
}

void CameraFirstPerson::ProcessKeyboard(glm::vec2 dir, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    pos += velocity * (front * dir.y + right * dir.x );
}

void CameraFirstPerson::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}

void CameraFirstPerson::ProcessMouseScroll(float yoffset) {
    zoom -= (float) yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void CameraFirstPerson::updateCameraVectors() {
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