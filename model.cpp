#include "model.hpp"

using namespace ParamWorld;

void Model::InitBuffer() {
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(
      GL_ARRAY_BUFFER,
      g_vertex_buffer_data.size() * 4, // number of elements times their size
      &g_vertex_buffer_data[0],
      GL_STATIC_DRAW
    );

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(
      GL_ARRAY_BUFFER,
      g_color_buffer_data.size() * 4,
      &g_color_buffer_data[0],
      GL_STATIC_DRAW
    );
}

void Model::drawBuffer() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
      0, // attribute 0, no reason for 0, but must match layout in shader
      3, // size
      GL_FLOAT, // type
      GL_FALSE, // normalized
      0,  // stride
      (void*)0 // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
      1,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)0
    );

    glDrawArrays(GL_TRIANGLES, 0, g_vertex_buffer_data.size()/3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

uint16_t Model::AddVertex(float x, float y, float z, const Color& c) {
    g_vertex_buffer_data.push_back(x);
    g_vertex_buffer_data.push_back(y);
    g_vertex_buffer_data.push_back(z);
    g_color_buffer_data.push_back(c.getRed());
    g_color_buffer_data.push_back(c.getGreen());
    g_color_buffer_data.push_back(c.getBlue());
    // TODO: change
    return 0;
}
