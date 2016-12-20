#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Color.hpp"

struct Vertex {
    const glm::vec3 pos;
    const glm::vec3 normal;
    const float u;
    const float v;
    const Color color;

    Vertex(const glm::vec3 pos, const glm::vec3 normal, const float u,
            const float v, const Color color) :
            pos(pos),
            normal(normal),
            u(u),
            v(v),
            color(color) {}
};



#endif
