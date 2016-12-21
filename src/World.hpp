#ifndef WORLD_HPP
#define WORLD_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <unordered_set>
#include <vector>

#include "Params/SceneParams.h"
#include "SceneObjects/SceneObject.hpp"
#include "SceneObjects/TreeObject.hpp"
#include "SceneObjects/RockObject.hpp"
#include "SceneObjects/SkyObject.hpp"

namespace ParamWorld {

struct Square {
    int x;
    int z;

    Square(int xx, int zz) : x(xx), z(zz) {}

    bool operator==(const Square s) const {
        return s.x == x && s.z == z;
    }
};
}

namespace std {
template<>
struct hash<ParamWorld::Square> {
    size_t operator()(const ParamWorld::Square &sq) const {
        return std::hash<int>()(sq.x) ^ std::hash<int>()(sq.z);
    }
};
}

namespace ParamWorld {

class World {
public:
    void Render(glm::mat4 Perspective, glm::vec3 position, glm::vec3 direction, glm::vec3 up);
    void updateExploredSquares(GLFWwindow *window, glm::vec3 playerPosition, float theta);
    World(float worldExtent, GLuint matID);

private:
    void AddMoreThings(float x, float z, float horizontalAngle);

    // The parameters that generate the new parts of the world.
    SceneParams sceneParams;
    // All objects (RockObjects, TreeObjects, etc.) in the world.
    std::vector<SceneObject> allObjects;
    // Objects that can still move the param means.
    std::vector<SceneObject> relevantObjects;
    // Model representing the floor and sky.
    Ground g;
    SkyObject s;

    // The set of all grid spaces that have been explored in this world. Kept at TODO intervals.
    std::unordered_set<Square> exploredSquares;

    GLuint MatrixID;

    double lastAdded = glfwGetTime();

    const float radius = 10.0f;
};
} // end namespace

#endif
