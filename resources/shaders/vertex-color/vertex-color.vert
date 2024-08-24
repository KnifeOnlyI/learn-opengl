#version 330 core

in vec3 position;
in vec3 color;

out vec3 vertexColor;

void main()
{
    // Inverse the y-axis of the vertex position to upside-down the drawing
    gl_Position = vec4(position.x, -position.y, position.z, 1.0);
    vertexColor = color;
}