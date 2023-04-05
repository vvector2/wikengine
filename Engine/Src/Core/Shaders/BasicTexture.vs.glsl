#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec2 uvIn;

uniform mat4 mvp;
out vec2 uv;

void main(){
    gl_Position =  mvp * vec4(vertexPosition_modelspace,1);
    uv = uvIn;
}

