#ifndef MODEL_HPP
#define MODEL_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include "Color.hpp"
#include "Vertex.hpp"

namespace ParamWorld {

class Model {
public:
    void InitBuffer();
    void drawBuffer() const;
    void AddBoxFromCorner(float x1, float y1, float z1,
                float x2, float y2, float z2,
                Color c);
    void AddBoxFromCorner(Color c, glm::vec3 origin, glm::vec3 size);
    void AddBoxFromCenter(Color c, glm::vec3 origin, glm::vec3 size);
    void AddTetra(Color color, glm::vec3 top, glm::vec3 l, glm::vec3 r, glm::vec3 b);
    void AddBoxFromCenter(Color c, glm::vec3 center, glm::vec3 size, glm::fquat rotation);

    Model() {}

protected:
    unsigned int AddVertex(Vertex v);
    void AddTriangle(unsigned int a, unsigned int b, unsigned int c);

private:
    GLuint _vertexbuffer, _colorbuffer, _normalbuffer, _elementbuffer;
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _colors;
    std::vector<GLfloat> _normals;
    std::vector<unsigned int> _elements;
    unsigned int _vertexCount;
};

}

#endif
