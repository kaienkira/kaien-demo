#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader_program.h"
#include "vertex_array.h"

class GLFWExitGuard {
public:
    ~GLFWExitGuard() { glfwTerminate(); }
};

static void keyCallback(GLFWwindow* window, int key, int scancode,
                 int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

static void render(ShaderProgram &shader_program,
                   VertexArray &vertex_array)
{
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program.getProgram());
    glBindVertexArray(vertex_array.getVAO());
    glDrawElements(GL_TRIANGLES, vertex_array.getElementCount(),
                   GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

int main()
{
    // init glfw
    if (glfwInit() != GLFW_TRUE) {
        std::cout << "init GLFW failed" << std::endl;
        return 1;
    }
    GLFWExitGuard glfw_exit_guard;

    // create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(
        800, 600, "Hello World", NULL, NULL);
    if (NULL == window) {
        std::cout << "create GLFW window failed" << std::endl;
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    // init glew
    glewExperimental = GL_TRUE;
    GLenum ret = glewInit();
    if (ret != GLEW_OK) {
        std::cout << "int GLEW failed: "
                  << glewGetErrorString(ret)
                  << std::endl;
        return 1;
    }

    // set view port
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // build shader program
    ShaderProgram shader_program;
    if (shader_program.init(
            "vertex.shader", "fragment.shader") == false) {
        std::cout << "load shader program failed" << std::endl;
        return 1;
    }

    // build vertex array
    VertexArray vertex_array;
    if (vertex_array.init("trangle.model") == false) {
        std::cout << "load model failed" << std::endl;
        return 1;
    }

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        render(shader_program, vertex_array);

        glfwSwapBuffers(window);
    }

    return 0;
}
