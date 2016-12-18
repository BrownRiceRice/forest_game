#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "/usr/local/include/GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ParamWorld {

class Player {
public:

  glm::vec3 position;

  float horizontalAngle;
  void computeMatricesFromInputs(GLFWwindow *window);
  glm::mat4 getViewMatrix() {
    return ViewMatrix;
  }
  glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
  }
  Player(glm::vec3 startPos) : lastTime(glfwGetTime()),
      position(startPos),
      horizontalAngle(3.14f),
      verticalAngle(0.0f),
      initialFoV(45.0f),
      speed(3.0f),
      mouseSpeed(0.005f * 10) {}

private:
  double lastTime;
  float verticalAngle;

  float initialFoV;

  float speed; // 3 units per second
  float mouseSpeed;

  glm::mat4 ProjectionMatrix;
  glm::mat4 ViewMatrix;
};

}

#endif
