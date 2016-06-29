#ifndef KAIEN_DEMO_OPENGL_HELLO_WORLD_H
#define KAIEN_DEMO_OPENGL_HELLO_WORLD_H

#include <string>
#include <vector>
#include <GL/glew.h>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    bool init(const std::vector<GLfloat> &vertices,
              const std::vector<GLuint> &indices);
    bool init(const std::string &model_file);

    GLuint getVAO() const { return vao_; }
    GLsizei getElementCount() const { return element_count_; }

private:
    struct ReadMode {
        enum type {
            NONE = -1,
            VERTICE = 0,
            INDICE = 1,
        };
    };

private:
    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;
    GLsizei element_count_;
};


#endif
