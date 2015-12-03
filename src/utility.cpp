//
// Created by dawid on 12/2/15.
//

#include "utility.hpp"

#include <format.h>
#include <easylogging++.h>


string readFile(string fileName)
{
    std::FILE *fp = std::fopen(fileName.c_str(), "rb");
    std::string contents;

    if (fp)
    {
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        std::fread(&contents[0], 1, contents.size(), fp);
        std::fclose(fp);
        return contents;
    }
    else
    {
        throw fmt::format("Couldn't read file {0}", fileName);
    }
}

GLuint compileShader(GLenum shaderType, string fileName)
{
    string shaderSourceStr = readFile(fileName);
    const char* shaderSource = shaderSourceStr.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    GLint logLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    GLsizei l = 0;
    vector<char> compileLog(logLength);
    glGetShaderInfoLog(shader, logLength, &logLength, &compileLog[0]);
    if(logLength != 0)
    {
        throw fmt::format("Error compiling shader {0}:\n{1}\n{2}", fileName, &compileLog[0], shaderSource);
    }
    else
    {
        LOG(INFO) << fmt::format("Shader {0} compiled successfully.", fileName);
    }
}

GLuint linkProgram(vector<GLuint> shaders)
{
    GLuint shaderProgram = glCreateProgram();
    for(auto& shader : shaders)
    {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);
    GLint logLength;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> linkLog(logLength);
    glGetProgramInfoLog(shaderProgram, logLength, &logLength, &linkLog[0]);
    if(logLength != 0)
    {
        throw fmt::format("Error linking program\n{0}", &linkLog[0]);
    }
    else
    {
        LOG(INFO) << "Program linked successfully.";
    }
}
