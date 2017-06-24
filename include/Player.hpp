#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Params/ParamArray.hpp"

namespace ParamWorld {

class Player {
public:
  glm::vec3 position;

  float horizontalAngle;

  /**
   * Polls inputs and updates player's position and viewing direction.
   */
  void updateCameraFromInputs(GLFWwindow *window);

  glm::mat4 getViewMatrix() {
      return ViewMatrix;
  }

  glm::vec3 getPosition() {
      return position;
  }

  glm::vec3 getDirection() {
      return direction;
  }

  glm::vec3 getUp() {
      return up;
  }

  const glm::mat4 getProjectionMatrix() const {
      return ProjectionMatrix;
  }

  Player(glm::vec3 startPos) : lastTime(glfwGetTime()),
      position(startPos),
      horizontalAngle(0.0f),
      verticalAngle(0.0f),
      initialFoV(45.0f),
      speed(3.0f),
      mouseSpeed(0.005f * 10),
      init(true) {}

private:
  double lastTime;
  float verticalAngle;

  float initialFoV;

  float speed; // 3 units per second
  float mouseSpeed;

  const glm::mat4 ProjectionMatrix =
          glm::perspective(initialFoV, 4.0f/3.0f, 0.1f, 1000.0f);
  glm::mat4 ViewMatrix;
  glm::vec3 direction;
  glm::vec3 up;

  bool init;
};

}

#endif
