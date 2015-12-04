#version 450

layout(location = 0) uniform mat4 MVP;


layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 color;

smooth out vec4 smoothColor;

void main()
{
    smoothColor = vec4(color, 1);
    gl_Position = MVP*vec4(vertex, 1);
    //gl_Position = vec4(vertex, 1);
}