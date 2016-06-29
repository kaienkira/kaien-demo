#include <cstddef>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLFWExitGuard {
public:
    ~GLFWExitGuard() { glfwTerminate(); }
};

class VertexArray {
public:
    VertexArray() :
        vao_(0), vbo_(0), ebo_(0)
    {
    }

    GLuint getVAO() const
    {
        return vao_;
    }

    void init(const std::vector<GLfloat> &vertices,
              const std::vector<GLuint> &indices)
    {
        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &ebo_);

        glBindVertexArray(vao_);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),
            &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
            &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
            3 * sizeof(GLfloat), (GLvoid *)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~VertexArray()
    {
        glDeleteVertexArrays(1, &vao_);
        glDeleteBuffers(1, &vbo_);
        glDeleteBuffers(1, &ebo_);
    }

private:
    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;
};

static void keyCallback(GLFWwindow* window, int key, int scancode,
                 int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

static GLuint buildShader(GLenum shader_type, const GLchar *shader_text)
{

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_text, NULL);
    glCompileShader(shader);

    GLint compile_status;
    GLchar info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (GL_FALSE == compile_status) {
        glGetShaderInfoLog(shader, sizeof(info_log), NULL, info_log);
        std::cout << "compile shader failed: "
                  << info_log << std::endl;
        return 0;
    }

    return shader;
}

static GLuint buildShaderProgram()
{
    const GLchar *vertex_shader_text =
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;"
        "void main()"
        "{"
        "    gl_Position = vec4(position.x, position.y, position.z, 1.0);"
        "}";

    GLuint vertex_shader = buildShader(
        GL_VERTEX_SHADER, vertex_shader_text);
    if (0 == vertex_shader) {
        std::cout << "build vertex shader failed" << std::endl;
        return 0;
    }

    const GLchar *fragment_shader_text =
        "#version 330 core\n"
        "out vec4 color;"
        "void main()"
        "{"
        "    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
        "}";

    GLuint fragment_shader = buildShader(
        GL_FRAGMENT_SHADER, fragment_shader_text);
    if (0 == vertex_shader) {
        std::cout << "build fragment shader failed" << std::endl;
        return 0;
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    GLint link_status;
    GLchar info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);
    if (GL_FALSE == link_status) {
        glGetProgramInfoLog(
            shader_program, sizeof(info_log), NULL, info_log);
        std::cout << "link shader program failed: "
                  << info_log << std::endl;
        return 0;
    }
    
    return shader_program;
}

static void render(GLuint shader_program, GLuint vao)
{
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
    GLuint shader_program = buildShaderProgram();
    if (0 == shader_program) {
        std::cout << "build shader program failed" << std::endl;
        return 1;
    }

    // build vertex array
    std::vector<GLfloat> vertices = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    std::vector<GLuint> indices = {
        0, 1, 3,
        1, 2, 3
    };

    VertexArray vertex_array;
    vertex_array.init(vertices, indices);

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        render(shader_program, vertex_array.getVAO());

        glfwSwapBuffers(window);
    }

    return 0;
}
