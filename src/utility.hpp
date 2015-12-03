#pragma once

#include <string>
#include <GL/glew.h>
#include <vector>
#include <cmath>

const float PI = (float)std::atan(1.0)*4;

using std::vector;
using std::string;

string readFile(string fileName);
GLuint compileShader(GLenum shaderType, string fileName);
GLuint linkProgram(vector<GLuint> shaders);