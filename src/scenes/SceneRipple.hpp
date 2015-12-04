#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using std::vector;
class SceneRipple
{
    struct Vertex
    {
        glm::vec3 position;
    };

    GLuint _shaderProgram = 0;
    GLuint _vao = 0;
    GLuint _vertexBuffer;
    GLuint _indexBuffer;

    mat4 _view;
    mat4 _proj;

    vector<Vertex> _vertices;
    vector<GLuint> _indices;

public:
    SceneRipple();
    ~SceneRipple();
    void draw();
};
