#version 450

layout(location = 0) uniform mat4 MVP;
layout(location = 1) uniform float time;

layout(location = 0) in vec3 vertex;

const float amplitude = 0.05;
const float frequency = 5;

const float PI = 3.14159;

void main()
{
    float distance = length(vertex);
    float y = amplitude*sin(-PI*distance*8+frequency*time);
    gl_Position = MVP*vec4(vertex.x, y, vertex.z,1);
}