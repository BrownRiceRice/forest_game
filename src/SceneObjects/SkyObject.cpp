#include "SceneObjects/SkyObject.hpp"
#include <iostream>

#define MATH_FLOAT_PI 3.1415926f

using namespace ParamWorld;

SkyObject::SkyObject(int starCount, glm::vec3 origin, float dist)
    : SceneObject(ParamArray<SP_Count>(), origin), lastTime(glfwGetTime())
{
    glm::vec3 maxSize(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < starCount; i++) {
        float u = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float v = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float theta = 2 * MATH_FLOAT_PI * u;
        float phi = 2 * MATH_FLOAT_PI * v;
        // std::cout << "Theta: " << theta << std::endl;
        // std::cout << "Phi: " << phi << std::endl;
        glm::vec3 yAxis = glm::vec3(0, 1, 0);
        glm::vec3 zAxis = glm::vec3(0, 0, 1);
        glm::vec3 pos = glm::rotate(glm::angleAxis(phi, yAxis) * glm::angleAxis(-theta, zAxis),
                                    origin - glm::vec3(dist, 0, 0));
        // std::cout << "Star pos: " << pos[0] << ", " << pos[1] << ", " << pos[2] << std::endl;
        float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
        float shade = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX)) / 3.0f;
        Color c(0.66f + shade, 0.66f + shade, 0.66f + shade);
        m.AddBoxFromCenter(c, pos, maxSize * x);
    }
}
