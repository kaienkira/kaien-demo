#include "vertex_array.h"

#include <fstream>
#include <iostream>
#include <sstream>

VertexArray::VertexArray() :
    vao_(0), vbo_(0), ebo_(0), element_count_(0)
{
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
}

bool VertexArray::init(const std::vector<GLfloat> &vertices,
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
    element_count_ = indices.size();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

bool VertexArray::init(const std::string &model_file)
{
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    std::ifstream fs("trangle.model");
    if (fs.is_open() == false) {
        std::cout << "can not open model file" << std::endl;
        return 0;
    }

    ReadMode::type read_mode = ReadMode::NONE;
    std::string line;
    while (std::getline(fs, line)) {
        if (line == "#vertice") {
            read_mode = ReadMode::VERTICE; 
            continue;
        } else if (line == "#indice") {
            read_mode = ReadMode::INDICE;
            continue;
        } else if (line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);

        if (read_mode == ReadMode::VERTICE) {
            while (!ss.eof()) {
                GLfloat v;
                ss >> v;
                vertices.push_back(v);
            }
        } else if (read_mode == ReadMode::INDICE) {
            while (!ss.eof()) {
                GLuint v;
                ss >> v;
                indices.push_back(v);
            }
        }
    }

    return init(vertices, indices);
}
