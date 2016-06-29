#include "shader_program.h"

#include <fstream>
#include <iostream>
#include <vector>

ShaderProgram::ShaderProgram() :
    program_(0)
{
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(program_);
}

bool ShaderProgram::init(const std::string &vertex_shader_file,
                         const std::string &fragment_shader_file)
{
    GLuint vertex_shader = compileShader(
        GL_VERTEX_SHADER, vertex_shader_file);
    if (0 == vertex_shader) {
        std::cout << "compile vertex shader failed" << std::endl;
        return false;
    }

    GLuint fragment_shader = compileShader(
        GL_FRAGMENT_SHADER, fragment_shader_file);
    if (0 == fragment_shader) {
        std::cout << "compile fragment shader failed" << std::endl;
        glDeleteShader(vertex_shader);
        return false;
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
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return false;
    }
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    program_ = shader_program;

    return true;
}

GLuint ShaderProgram::compileShader(GLenum shader_type,
                                    const std::string &shader_file)
{
    std::ifstream fs(shader_file.c_str(), std::ios::binary | std::ios::ate);
    if (fs.is_open() == false) {
        std::cout << "can not open shader file: "
                  << shader_file << std::endl;
        return 0;
    }

    size_t file_size = fs.tellg();
    std::vector<GLchar> input_buffer(file_size + 1);
    fs.seekg(0);
    input_buffer.assign((std::istreambuf_iterator<GLchar>(fs)),
                        (std::istreambuf_iterator<GLchar>()));

    GLuint shader = glCreateShader(shader_type);
    const GLchar *shader_text = &input_buffer[0];
    glShaderSource(shader, 1, &shader_text, NULL);
    glCompileShader(shader);

    GLint compile_status;
    GLchar info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (GL_FALSE == compile_status) {
        glGetShaderInfoLog(shader, sizeof(info_log), NULL, info_log);
        std::cout << "compile shader failed:" << std::endl
                  << info_log << std::endl;
        return 0;
    }

    return shader;
}
