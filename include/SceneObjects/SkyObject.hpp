#ifndef SKYOBJECT_HPP
#define SKYOBJECT_HPP

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include "SceneObject.hpp"
#include "headers.hpp"

namespace ParamWorld
{
class SkyObject : public SceneObject
{
   public:
    virtual glm::mat4 calcModelMatrix()
    {
        double currentTime = glfwGetTime();
        skyTurn += (skyTurnSpeed * (currentTime - lastTime));
        lastTime = currentTime;
        return glm::rotate(skyTurn, glm::vec3(1, 0, 0));
    }

    SkyObject(int starCount, glm::vec3 origin, float dist);

   private:
    double lastTime;
    // The amount radians that the stars turn.
    float skyTurn = 0.0;
    const float skyTurnSpeed = 0.02f;
};
}

#endif
