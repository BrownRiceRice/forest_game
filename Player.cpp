#include "Player.hpp"

using namespace ParamWorld;

void Player::computeMatricesFromInputs(GLFWwindow *window) {
    static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();

    float deltaTime = float(currentTime - lastTime);
    // Compute angles.
    // Start with mouse position
    double xpos, ypos;
    //glfwGetCursorPos(window, &xpos, &ypos);
    //glfwSetCursorPos(window, 1024/2, 768/2);


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        verticalAngle += deltaTime * mouseSpeed * 10;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        verticalAngle -= deltaTime * mouseSpeed * 10;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        horizontalAngle -= deltaTime * mouseSpeed * 10;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        horizontalAngle += deltaTime * mouseSpeed * 10;
    }

    //horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos);
    // -= because I like inverted y-axis stuff
    //verticalAngle -= mouseSpeed * deltaTime * float(768/2 - ypos);

    glm::vec3 front(
      sin(horizontalAngle),
      0,
      cos(horizontalAngle)
    );

    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14159f/2.0f),
        0,
        cos(horizontalAngle - 3.14159f/2.0f)
    );

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        position += front * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= front * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    glm::vec3 up = glm::cross(right, direction);

    ProjectionMatrix = glm::perspective(initialFoV, 4.0f/3.0f, 0.1f, 100.0f);
    ViewMatrix = glm::lookAt(position, position + direction, up);

    lastTime = currentTime;
}
