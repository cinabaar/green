#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <input/Input.hpp>

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
    GLuint _vertexBuffer = 0;
    GLuint _indexBuffer = 0;

    mat4 _view;
    mat4 _proj;
    mat4 _model;

    vector<Vertex> _vertices;
    vector<GLuint> _indices;

    bool _rotateLeft = false;
    bool _rotateRight = false;
public:
    SceneRipple();
    ~SceneRipple();
    void onKeyPressed(Input::KeyVariables variables);
    void draw();
    void update(float deltaTime);


};
