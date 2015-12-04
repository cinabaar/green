#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class SceneTriangle
{
private:
    GLuint _shaderProgram = 0;
    GLuint _vao = 0;
    GLuint _vertexBuffer;
    GLuint _indexBuffer;

    mat4 _view;
    mat4 _proj;

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
    };
public:
    SceneTriangle();
    ~SceneTriangle();
    void draw();

};
