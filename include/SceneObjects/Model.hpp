#ifndef MODEL_HPP
#define MODEL_HPP

#include "headers.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include "Color.hpp"

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
    //uint16_t AddVertex(float x, float y, float z, const Color& c);

    Model() {}

protected:
    uint16_t AddVertex(float x, float y, float z, const Color& c);

private:
    GLuint _vertexbuffer, _colorbuffer, _normalbuffer;
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _colors;
    std::vector<GLfloat> _normals;
};

}

#endif
