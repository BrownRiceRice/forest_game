#ifndef MODEL_H
#define MODEL_H

#include "/usr/local/include/GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

namespace ParamWorld {

class Color {
public:
    Color(float r, float g, float b) : red(r), green(g), blue(b) {}
    float getRed() const { return red; }
    float getBlue() const { return blue; }
    float getGreen() const { return green; }

private:
    float red, green, blue;

};

class Model {
public:
    void InitBuffer();
    void drawBuffer();
    //void AddBox(Color c, float x1, float y1, float z1,
    //                     float x2, float y2, float z2);
    //void AddBox(Color c, glm::vec3 origin, glm::vec3 size);
    //void AddTetra(Color color, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
    //void AddBox(Color c, glm::vec3 origin, glm::vec3 size, glm::fquat rotation);
    uint16_t AddVertex(float x, float y, float z, const Color& c);

    Model() {}

protected:
    //uint16_t AddVertex(float x, float y, float z, const Color& c);

private:
    GLuint vertexbuffer, colorbuffer;
    std::vector<GLfloat> g_vertex_buffer_data;
    std::vector<GLfloat> g_color_buffer_data;
};

}

#endif
