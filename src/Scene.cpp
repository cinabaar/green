//
// Created by dawid on 12/2/15.
//

#include "Scene.hpp"

#include "utility.hpp"
#include <format.h>
#include <easylogging++.h>
#include <glm/gtc/matrix_transform.hpp>

using std::vector;


Scene::Scene()
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, "shaders/vertex.glsl");
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");
    _shaderProgram = linkProgram({{vertexShader, fragmentShader}});
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glCreateVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    vector<Vertex> vertices {
            {vec3(-1, -1, 0), vec3(1, 0, 0)},
            {vec3(0, 1, 0), vec3(0, 1, 0)},
            {vec3(1, -1, 0), vec3(0, 0, 1)}
    };
    vector<int> indices {{1, 2, 3}};

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0], GL_STATIC_DRAW);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

    view = glm::lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
    proj = glm::perspective(PI/6, 16.f/9, 0.1f, 100f);
}

void Scene::draw()
{
}

Scene::~Scene()
{
    glDeleteProgram(_shaderProgram);
}
