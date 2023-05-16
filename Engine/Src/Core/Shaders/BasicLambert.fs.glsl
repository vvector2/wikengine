#version 330 core

in vec3 color;
in vec2 uv;
in float visibilityNormal;

out vec3 colorOut;

uniform sampler2D textureSampler0;
uniform int textureEnable;

void main() {
    vec3 MaterialDiffuseColor = texture(textureSampler0, uv).rgb;
    colorOut = (MaterialDiffuseColor + color) * visibilityNormal;
}
