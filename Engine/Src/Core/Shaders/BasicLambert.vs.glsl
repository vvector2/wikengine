#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec2 vertexUV;

uniform mat4 mvp;

out vec3 color;
out vec3 normal;
out vec2 uv;

void main(){
    gl_Position =  mvp * vec4(vertexPos,1);
    color = vertexColor;
    normal = vertexNormal;
    uv = vertexUV;
}
