#version 330 core

in vec3 color;
in vec3 normal;
in vec2 uv;

out vec3 colorOut;

uniform sampler2D textureSampler0;
uniform bool textureEnable
uniform vec3 directionalLight

void main(){
    float visibility = clamp(dot(normal, -directionalLight), 0, 1);
    colorOut = (texture( textureSampler0, uv ).rgb * textureEnable + color) * visibility;
}
