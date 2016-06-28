#include <cstddef>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLFWExitGuard {
public:
    ~GLFWExitGuard() { glfwTerminate(); }
};

void keyCallback(GLFWwindow* window, int key, int scancode,
                 int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void render()
{
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
    // init glfw
    if (glfwInit() != GLFW_TRUE) {
        std::cout << "Failed to initialize GLFW" << std::endl;
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
        std::cout << "Failed to create GLFW window" << std::endl;
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    // init glew
    glewExperimental = GL_TRUE;
    GLenum ret = glewInit();
    if (ret != GLEW_OK) {
        std::cout << "Failed to initialize GLEW: "
                  << glewGetErrorString(ret)
                  << std::endl;
        return 1;
    }

    // set view port
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        render();

        glfwSwapBuffers(window);
    }

    return 0;
}
