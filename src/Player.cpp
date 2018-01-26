#include "Player.hpp"
#include <iostream>

using namespace ParamWorld;

void Player::updateCameraFromInputs(GLFWwindow *window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    double currentTime = glfwGetTime();
    if (init) {
        // Fixes an issues where the mouse would be set to the center, but that
        // movement would cause a view shift rapidly at the beginning of the
        // game.
        if (currentTime - lastTime < .1f) {
            return;
        }
        glfwSetCursorPos(window, width / 2, height / 2);
        init = false;
    }
    float deltaTime = float(currentTime - lastTime);
    // Compute angles.
    // Start with mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, width / 2, height / 2);

    horizontalAngle += mouseSpeed * deltaTime * float(width / 2 - xpos);
    // -= because I like inverted y-axis stuff
    verticalAngle += mouseSpeed * deltaTime * float(height / 2 - ypos);

    glm::vec3 front(sin(horizontalAngle), 0, cos(horizontalAngle));

    glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14159f / 2.0f), 0,
                                cos(horizontalAngle - 3.14159f / 2.0f));

    if (glfwGetKey(window, MOVE_FORWARD) == GLFW_PRESS) {
        position += front * deltaTime * speed;
    }
    if (glfwGetKey(window, MOVE_BACKWARD) == GLFW_PRESS) {
        position -= front * deltaTime * speed;
    }
    if (glfwGetKey(window, MOVE_RIGHT) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    if (glfwGetKey(window, MOVE_LEFT) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle),
                          cos(verticalAngle) * cos(horizontalAngle));

    up = glm::cross(right, direction);

    ViewMatrix = glm::lookAt(position, position + direction, up);

    lastTime = currentTime;
}
