#include <iostream>
#include <format.h>
#include <easylogging++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "scenes/SceneRipple.hpp"
#include "scenes/SceneTriangle.hpp"

INITIALIZE_EASYLOGGINGPP

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;
const char* WINDOW_TITLE = "Green";

using std::string;

int main()
{
    if(!glfwInit())
    {
        LOG(ERROR) << "Unable to initialize GLFW";
        return -1;
    }

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        LOG(ERROR)<<fmt::format("Initializing GLEW failed with error:\n{0}", glewGetErrorString(err));
        return -2;
    }
    LOG(INFO) << fmt::format("Initialized OpenGL context\n{0}\n{1}\n{2}",
                             glGetString(GL_VERSION),
                             glGetString(GL_VENDOR),
                             glGetString(GL_RENDERER));

    try
    {
        SceneRipple scene;

        while(!glfwWindowShouldClose(window))
        {
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            scene.draw();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    catch(string error)
    {
        LOG(ERROR) << error;
    }

    return 0;
}
