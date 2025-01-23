#include <iostream>


#include "mesh.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


GLuint Mesh::get_index_count() const {
    return index_count;
}

void Mesh::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Mesh::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::cleanup() const {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

