#ifndef KAIEN_DEMO_HELLO_WORLD_SHADER_PROGRAM_H
#define KAIEN_DEMO_HELLO_WORLD_SHADER_PROGRAM_H

#include <string>
#include <GL/glew.h>

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    bool init(const std::string &vertex_shader_file,
              const std::string &fragment_shader_file);

    GLuint getProgram() const { return program_; }

private:
    GLuint compileShader(GLenum shader_type, const std::string &shader_file);

private:
    GLuint program_;
};

#endif
