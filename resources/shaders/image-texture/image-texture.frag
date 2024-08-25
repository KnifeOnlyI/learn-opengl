#version 330 core

out vec4 fragmentColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D uTexture;

void main()
{
    fragmentColor = texture(uTexture, texCoord) * vec4(color, 1.0);
}