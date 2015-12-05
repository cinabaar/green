#include "SceneRipple.hpp"

#include "utility.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <easylogging++.h>
#include <format.h>
#include <chrono>
#include "input/Input.hpp"
#include <glm/gtc/quaternion.hpp>

SceneRipple::SceneRipple()
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, "shaders/ripple/vertex.glsl");
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, "shaders/ripple/fragment.glsl");
    _shaderProgram = linkProgram({{vertexShader, fragmentShader}});
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    const uint32_t resX = 31;
    const uint32_t resZ = 31;
    const GLfloat sizeX = 1;
    const GLfloat sizeZ = 1;

    for(auto z=0; z < resZ; z++)
    {
        for(auto x=0; x < resX; x++)
        {
            _vertices.push_back(
                    {vec3(float(x)/resX * sizeX, 0, float(z)/resZ * sizeZ)-vec3(sizeX/2.f, 0, sizeZ/2.f)}
            );
            //auto& pos = vertices.back().position;
            //LOG(INFO) << fmt::format("({0}, {1}, {2})", pos.x, pos.y, pos.z);
        }
    }

    for(auto z=0; z < resZ-1; z++)
    {
        for(auto x=0; x < resX-1; x++)
        {
            GLuint ul = z * resX + x;
            GLuint ur = ul + 1;
            GLuint bl = ul + resX;
            GLuint br = bl + 1;
            if(x%2 == 0)
            {
                _indices.insert(_indices.end(), {ul, bl, ur});
                _indices.insert(_indices.end(), {ur, bl, br});
            }
            else
            {
                _indices.insert(_indices.end(), {ul, br, bl});
                _indices.insert(_indices.end(), {ul, ur, br});
            }
        }
    }
    /*for(int i=0; i < _indices.size(); i+=3)
    {
        auto& vert1 = _vertices[_indices[i]];
        auto& vert2 = _vertices[_indices[i + 1]];
        auto& vert3 = _vertices[_indices[i + 2]];

        LOG(INFO) << fmt::format("({0}, {1}, {2}), ({3}, {4}, {5}), ({6}, {7}, {8})",
                                 vert1.position.x,
                                 vert1.position.y,
                                 vert1.position.z,
                                 vert2.position.x,
                                 vert2.position.y,
                                 vert2.position.z,
                                 vert3.position.x,
                                 vert3.position.y,
                                 vert3.position.z
        );
    }*/

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferStorage(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), &_indices[0], GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);


    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexBuffer(0, _vertexBuffer, 0, sizeof(Vertex));

    _view = glm::lookAt(vec3(0, 2, 3), vec3(0, 0, 0), vec3(0, 1, 0));
    _proj = glm::perspective(PI/4, 16.f/9.f, 0.1f, 100.f);
    _model = mat4(1);

    glBindVertexArray(0);

    Input::get().keyAction.connect<SceneRipple, &SceneRipple::onKeyPressed>(this);

}

SceneRipple::~SceneRipple()
{
    glDeleteProgram(_shaderProgram);
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_indexBuffer);
    glDeleteVertexArrays(1, &_vao);
    Input::get().keyAction.disconnect<SceneRipple, &SceneRipple::onKeyPressed>(this);
}

void SceneRipple::draw()
{
    glUseProgram(_shaderProgram);
    glBindVertexArray(_vao);
    mat4 mvp = _proj * _view * _model;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



void SceneRipple::update(float deltaTime)
{
    static float timeSum = 0;
    timeSum += deltaTime;
    glUseProgram(_shaderProgram);
    glUniform1f(1, timeSum);
    if(_rotateLeft)
    {
        _model *= glm::mat4_cast(glm::angleAxis(-PI / 4 * deltaTime, vec3(0, 1, 0)));
    }
    if(_rotateRight)
    {
        _model *= glm::mat4_cast(glm::angleAxis(PI / 4 * deltaTime, vec3(0, 1, 0)));
    }
}


void SceneRipple::onKeyPressed(Input::KeyVariables variables)
{
    if(variables.key == GLFW_KEY_LEFT && variables.action == GLFW_PRESS)
    {
        _rotateLeft = true;
    }
    if(variables.key == GLFW_KEY_LEFT && variables.action == GLFW_RELEASE)
    {
        _rotateLeft = false;
    }
    if(variables.key == GLFW_KEY_RIGHT && variables.action == GLFW_PRESS)
    {
        _rotateRight = true;
    }
    if(variables.key == GLFW_KEY_RIGHT && variables.action == GLFW_RELEASE)
    {
        _rotateRight = false;
    }
}