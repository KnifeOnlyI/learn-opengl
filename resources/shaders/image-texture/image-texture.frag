#version 330 core

out vec4 fragmentColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec2 flippedXCoord = vec2(-texCoord.x, texCoord.y);

    fragmentColor = mix(texture(texture1, flippedXCoord), texture(texture2, texCoord), 0.5);
}