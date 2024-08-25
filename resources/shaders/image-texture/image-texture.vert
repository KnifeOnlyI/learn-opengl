#version 330 core

in vec3 vertexPosition;
in vec3 vertexColor;
in vec2 vertexTexCoord;

out vec3 color;
out vec2 texCoord;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0);
    color = vertexColor;
    texCoord = vertexTexCoord;
}