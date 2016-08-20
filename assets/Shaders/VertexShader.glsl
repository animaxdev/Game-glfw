#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;

uniform float xOffset;
uniform float YOffset;

void main()
{
    gl_Position = vec4(position.x + xOffset, position.y + YOffset, position.z, 1.0f);
    ourColor = color;
}