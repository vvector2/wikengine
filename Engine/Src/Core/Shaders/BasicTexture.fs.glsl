#version 330 core

in vec2 uv;

out vec3 color;

uniform sampler2D textureSampler0;

void main(){
    color = texture( textureSampler0, uv ).rgb;
}