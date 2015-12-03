#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class Scene
{
private:
    GLuint _shaderProgram;
    GLuint _vao;

    mat4 view;
    mat4 proj;

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
    };
public:
    Scene();
    ~Scene();
    void draw();

};
