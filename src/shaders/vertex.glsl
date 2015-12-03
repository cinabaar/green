#version 330

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 color;

smooth out vec4 smoothColor;
uniform mat4 MVP;

void main()
{
    smoothColor = vec4(color, 1);
    gl_Position = MVP*vec4(vertex, 1);
}