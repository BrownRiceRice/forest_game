#include "SceneObjects/Model.hpp"
#include <stdio.h>

using namespace ParamWorld;

void Model::InitBuffer()
{
    glGenBuffers(1, &_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 _vertices.size() * 4,  // number of elements times their size
                 &_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &_colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, _colors.size() * 4, &_colors[0], GL_STATIC_DRAW);

    glGenBuffers(1, &_normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0],
                 GL_STATIC_DRAW);
}

void Model::drawBuffer() const
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
    glVertexAttribPointer(0,  // attribute 0, no reason for 0, but must match layout in shader
                          3,  // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized
                          0,         // stride
                          nullptr    // array buffer offset
                          );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, _normalbuffer);
    glVertexAttribPointer(2,         // attribute
                          3,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          nullptr    // array buffer offset
                          );

    glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Model::AddBoxFromCorner(float x1, float y1, float z1, float x2, float y2, float z2, Color c)
{
    // Order the inputs.
    float t;
    if (x1 > x2) {
        t = x1;
        x1 = x2;
        x2 = t;
    }
    if (y1 > y2) {
        t = y1;
        y1 = y2;
        y2 = t;
    }
    if (z1 > z2) {
        t = z1;
        z1 = z2;
        z2 = t;
    }
    float vs[] = {
        x1, y1, z1, x1, y1, z2, x1, y2, z2, x1, y2, z2, x1, y2, z1, x1, y1, z1,  // left face end
        x2, y1, z1, x2, y1, z2, x2, y2, z2, x2, y2, z2, x2, y2, z1, x2, y1, z1,  // right face end
        x1, y1, z1, x1, y1, z2, x2, y1, z2, x2, y1, z2, x2, y1, z1, x1, y1, z1,  // bottom face end
        x1, y2, z1, x1, y2, z2, x2, y2, z2, x2, y2, z2, x2, y2, z1, x1, y2, z1,  // top face end
        x1, y1, z1, x1, y2, z1, x2, y2, z1, x2, y2, z1, x2, y1, z1, x1, y1, z1,  // back face end
        x1, y1, z2, x1, y2, z2, x2, y2, z2, x2, y2, z2, x2, y1, z2, x1, y1, z2,  // back face end
    };

    //_vertices.insert(_vertices.end(), temp.begin(), temp.end());
    for (int i = 0; i < 12; i++) {  // loop per triangle
        // Calculate normal for triangle.
        glm::vec3 one(vs[i], vs[i + 1], vs[i + 2]);
        glm::vec3 two(vs[i + 3], vs[i + 4], vs[i + 5]);
        glm::vec3 three(vs[i + 6], vs[i + 7], vs[i + 9]);
        glm::vec3 edge1 = two - one;
        glm::vec3 edge2 = three - one;
        glm::vec3 n = glm::normalize(glm::cross(edge1, edge2));
        for (int j = 0; j < 3; j++) {  // loop per vertex
            // Add 3 coordinates for vertex.
            for (int k = 0; k < 3; k++) {  // loop per number
                _vertices.push_back(vs[i * 9 + j * 3 + k]);
            }
            // Add colors for vertex.
            _colors.push_back(c.getRed());
            _colors.push_back(c.getGreen());
            _colors.push_back(c.getBlue());
            // Add normal for vertex.
            _normals.push_back(n[0]);
            _normals.push_back(n[1]);
            _normals.push_back(n[2]);
        }
    }
}

void Model::AddBoxFromCorner(Color c, glm::vec3 origin, glm::vec3 size)
{
    AddBoxFromCorner(origin[0], origin[1], origin[2], origin[0] + size[0], origin[1] + size[1],
                     origin[2] + size[2], c);
}

void Model::AddBoxFromCenter(Color c, glm::vec3 origin, glm::vec3 size)
{
    glm::vec3 o = origin - (size * 0.5f);
    AddBoxFromCorner(o[0], o[1], o[2], o[0] + size[0], o[1] + size[1], o[2] + size[2], c);
}

void Model::AddTetra(Color color, glm::vec3 top, glm::vec3 l, glm::vec3 r, glm::vec3 b)
{
    float vs[] = {top[0], top[1], top[2], l[0], l[1], l[2], r[0], r[1], r[2],
                  top[0], top[1], top[2], b[0], b[1], b[2], l[0], l[1], l[2],
                  top[0], top[1], top[2], b[0], b[1], b[2], r[0], r[1], r[2],
                  top[0], top[1], top[2], b[0], b[1], b[2], r[0], r[1], r[2]};
    for (int i = 0; i < 4; i++) {  // loop per triangle
        // Calculate normal for triangle.
        glm::vec3 one(vs[i], vs[i + 1], vs[i + 2]);
        glm::vec3 two(vs[i + 3], vs[i + 4], vs[i + 5]);
        glm::vec3 three(vs[i + 6], vs[i + 7], vs[i + 9]);
        glm::vec3 edge1 = two - one;
        glm::vec3 edge2 = three - one;
        glm::vec3 n = glm::normalize(glm::cross(edge1, edge2));
        for (int j = 0; j < 3; j++) {  // loop per vertex
            // Add 3 coordinates for vertex.
            for (int k = 0; k < 3; k++) {  // loop per number
                _vertices.push_back(vs[i * 9 + j * 3 + k]);
            }
            // Add colors for vertex.
            _colors.push_back(color.getRed());
            _colors.push_back(color.getGreen());
            _colors.push_back(color.getBlue());
            // Add normal for vertex.
            _normals.push_back(n[0]);
            _normals.push_back(n[1]);
            _normals.push_back(n[2]);
        }
    }
    // std::vector<float> temp(verts, verts+(3*12));
    //_vertices.insert(_vertices.end(), temp.begin(), temp.end());
    // for (int i = 0; i < 12; i++) {
    //    _colors.push_back(color.getRed());
    //    _colors.push_back(color.getGreen());
    //    _colors.push_back(color.getBlue());
    //}
}

void Model::AddBoxFromCenter(Color c, glm::vec3 center, glm::vec3 size, glm::fquat rotation)
{
    glm::vec3 s = size * 0.5f;
    glm::vec3 o = center;
    std::vector<glm::vec3> vecsOToPs;
    vecsOToPs.push_back(glm::vec3(-s[0], s[1], -s[2]));
    vecsOToPs.push_back(glm::vec3(s[0], s[1], -s[2]));
    vecsOToPs.push_back(glm::vec3(-s[0], -s[1], -s[2]));
    vecsOToPs.push_back(glm::vec3(s[0], -s[1], -s[2]));
    vecsOToPs.push_back(glm::vec3(-s[0], s[1], s[2]));
    vecsOToPs.push_back(glm::vec3(s[0], s[1], s[2]));
    vecsOToPs.push_back(glm::vec3(-s[0], -s[1], s[2]));
    vecsOToPs.push_back(glm::vec3(s[0], -s[1], s[2]));

    std::vector<glm::vec3> vs;
    for (auto& vecsOToP : vecsOToPs) {
        vs.push_back(glm::rotate(rotation, vecsOToP) + o);
    }

    float verts[] = {
        vs[3][0], vs[3][1], vs[3][2], vs[1][0], vs[1][1], vs[1][2],
        vs[0][0], vs[0][1], vs[0][2], vs[0][0], vs[0][1], vs[0][2],
        vs[2][0], vs[2][1], vs[2][2], vs[3][0], vs[3][1], vs[3][2],  // face 1 end

        vs[6][0], vs[6][1], vs[6][2], vs[4][0], vs[4][1], vs[4][2],
        vs[5][0], vs[5][1], vs[5][2], vs[4][0], vs[4][1], vs[4][2],
        vs[7][0], vs[7][1], vs[7][2], vs[6][0], vs[6][1], vs[6][2],  // face 2 end

        vs[6][0], vs[6][1], vs[6][2], vs[2][0], vs[2][1], vs[2][2],
        vs[0][0], vs[0][1], vs[0][2], vs[0][0], vs[0][1], vs[0][2],
        vs[4][0], vs[4][1], vs[4][2], vs[6][0], vs[6][1], vs[6][2],  // face 3 end

        vs[7][0], vs[7][1], vs[7][2], vs[5][0], vs[5][1], vs[5][2],
        vs[1][0], vs[1][1], vs[1][2], vs[1][0], vs[1][1], vs[1][2],
        vs[3][0], vs[3][1], vs[3][2], vs[7][0], vs[7][1], vs[7][2],  // face 4 end

        vs[3][0], vs[3][1], vs[3][2], vs[2][0], vs[2][1], vs[2][2],
        vs[6][0], vs[6][1], vs[6][2], vs[6][0], vs[6][1], vs[6][2],
        vs[7][0], vs[7][1], vs[7][2], vs[3][0], vs[3][1], vs[3][2],  // face 5 end

        vs[0][0], vs[0][1], vs[0][2], vs[1][0], vs[1][1], vs[1][2],
        vs[5][0], vs[5][1], vs[5][2], vs[5][0], vs[5][1], vs[5][2],
        vs[4][0], vs[4][1], vs[4][2], vs[0][0], vs[0][1], vs[0][2]  // face 6 end
    };

    for (int i = 0; i < 12; i++) {  // loop per triangle
        // Calculate normal for triangle.
        glm::vec3 one(verts[i], verts[i + 1], verts[i + 2]);
        glm::vec3 two(verts[i + 3], verts[i + 4], verts[i + 5]);
        glm::vec3 three(verts[i + 6], verts[i + 7], verts[i + 9]);
        glm::vec3 edge1 = two - one;
        glm::vec3 edge2 = three - one;
        glm::vec3 n = glm::normalize(glm::cross(edge1, edge2));
        for (int j = 0; j < 3; j++) {  // loop per vertex
            // Add 3 coordinates for vertex.
            for (int k = 0; k < 3; k++) {  // loop per number
                _vertices.push_back(verts[i * 9 + j * 3 + k]);
            }
            // Add colors for vertex.
            _colors.push_back(c.getRed());
            _colors.push_back(c.getGreen());
            _colors.push_back(c.getBlue());
            // Add normal for vertex.
            _normals.push_back(n[0]);
            _normals.push_back(n[1]);
            _normals.push_back(n[2]);
        }
    }
    /*
    std::vector<float> temp(verts, verts+(3*36));
    _vertices.insert(_vertices.end(), temp.begin(), temp.end());
    for (int i = 0; i < 36; i++) {
        _colors.push_back(c.getRed());
        _colors.push_back(c.getGreen());
        _colors.push_back(c.getBlue());
    }
    */
}

/*uint16_t Model::AddVertex(float x, float y, float z, const Color& c) {
    g_vertex_buffer_data.push_back(x);
    g_vertex_buffer_data.push_back(y);
    g_vertex_buffer_data.push_back(z);
    g_color_buffer_data.push_back(c.getRed());
    g_color_buffer_data.push_back(c.getGreen());
    g_color_buffer_data.push_back(c.getBlue());
    // TODO: change
    return 0;
} */
