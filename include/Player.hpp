#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <yaml-cpp/yaml.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Params/ParamArray.hpp"
#include "headers.hpp"

namespace ParamWorld
{
class Player
{
   public:
    glm::vec3 position;

    float horizontalAngle;

    /**
     * Polls inputs and updates player's position and viewing direction.
     */
    void updateCameraFromInputs(GLFWwindow *window);

    glm::mat4 getViewMatrix() { return ViewMatrix; }
    glm::vec3 getPosition() { return position; }
    glm::vec3 getDirection() { return direction; }
    glm::vec3 getUp() { return up; }
    const glm::mat4 getProjectionMatrix() const { return ProjectionMatrix; }
    Player(glm::vec3 startPos)
        : lastTime(glfwGetTime()),
          position(startPos),
          horizontalAngle(0.0f),
          verticalAngle(0.0f),
          initialFoV(45.0f),
          speed(3.0f),
          mouseSpeed(0.005f * 10),
          init(true)
    {
        // Be lazy and load keymappings in here.
        configureMappings();
    }

    void configureMappings()
    {
        YAML::Node config = YAML::LoadFile("../config/keymappings.yaml");
        MOVE_FORWARD = config["Qwerty"]["MOVE_FORWARD"].as<int>();
        MOVE_BACKWARD = config["Qwerty"]["MOVE_BACKWARD"].as<int>();
        MOVE_RIGHT = config["Qwerty"]["MOVE_RIGHT"].as<int>();
        MOVE_LEFT = config["Qwerty"]["MOVE_LEFT"].as<int>();
    }

   private:
    double lastTime;
    float verticalAngle;

    float initialFoV;

    float speed;  // 3 units per second
    float mouseSpeed;

    const glm::mat4 ProjectionMatrix = glm::perspective(initialFoV, 4.0f / 3.0f, 0.1f, 1000.0f);
    glm::mat4 ViewMatrix;
    glm::vec3 direction;
    glm::vec3 up;

    int MOVE_FORWARD;
    int MOVE_BACKWARD;
    int MOVE_LEFT;
    int MOVE_RIGHT;

    bool init;
};
}

#endif
