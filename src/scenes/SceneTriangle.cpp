//
// Created by dawid on 12/2/15.
//

#include "SceneTriangle.hpp"

#include "utility.hpp"
#include <format.h>
#include <easylogging++.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::vector;


SceneTriangle::SceneTriangle()
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, "shaders/triangle/vertex.glsl");
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, "shaders/triangle/fragment.glsl");
    _shaderProgram = linkProgram({{vertexShader, fragmentShader}});
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    vector<Vertex> vertices {
            {vec3(-1, -1, 0), vec3(1, 0, 0)},
            {vec3(0, 1, 0), vec3(0, 1, 0)},
            {vec3(1, -1, 0), vec3(0, 0, 1)}
    };
    vector<GLuint> indices {{0, 1, 2}};


    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferStorage(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],  GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0],  GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);


    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT));
    glVertexAttribBinding(1, 0);
    glEnableVertexAttribArray(1);

    glBindVertexBuffer(0, _vertexBuffer, 0, sizeof(Vertex));

    _view = glm::lookAt(vec3(0, 0, 3), vec3(0, 0, 0), vec3(0, 1, 0));
    _proj = glm::perspective(PI/4, 16.f/9.f, 0.1f, 100.f);

    glBindVertexArray(0);
}

void SceneTriangle::draw()
{
    glUseProgram(_shaderProgram);
    glBindVertexArray(_vao);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    mat4 mvp = _proj * _view;
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

SceneTriangle::~SceneTriangle()
{
    glDeleteProgram(_shaderProgram);
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_indexBuffer);
    glDeleteVertexArrays(1, &_vao);
}
