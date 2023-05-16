#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 vertexNormal;
layout (location = 3) in vec2 vertexUV;

uniform mat4 cameraMatrix;
uniform mat4 worldMatrix;
uniform vec3 directionalLight;

out vec3 color;
out float visibilityNormal;
out vec2 uv;

void main() {
    gl_Position = cameraMatrix * worldMatrix * vec4(vertexPos, 1);

    color = vertexColor;

    mat4 rotationScaleWorldMatrix = mat4(worldMatrix);
    rotationScaleWorldMatrix[3] = vec4(0, 0, 0, 1);

    visibilityNormal = dot(normalize((rotationScaleWorldMatrix * vec4(vertexNormal, 1)).xyz), -normalize(directionalLight));
    visibilityNormal = visibilityNormal < 0.f ? 0.f : visibilityNormal;

    uv = vertexUV;
}
