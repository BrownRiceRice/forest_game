#include "World.hpp"
#include <iostream>

using namespace ParamWorld;

World::World(float worldExtent, GLuint matID) :
        sceneParams(),
        g(Ground(worldExtent)),
        s(SkyObject(300, glm::vec3(0, 0, 0), 300.0f)),
        MatrixID(matID) {
    g.init();
    s.init();
}

void World::Render(glm::mat4 Perspective, glm::vec3 position, glm::vec3 direction, glm::vec3 up) {
    glm::mat4 View = glm::lookAt(position, position + direction, up);
    for (auto & allObject : allObjects) {
        glm::mat4 ModelM = allObject.calcModelMatrix();
        glm::mat4 mvp = Perspective * View * ModelM;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        allObject.draw();
    }
    glm::mat4 stationaryView = glm::lookAt(glm::vec3(0, position[1], 0), glm::vec3(0, position[1], 0) + direction, up);

    // draw ground
    glm::mat4 ModelM = g.calcModelMatrix();
    glm::mat4 mvp = Perspective * stationaryView * ModelM;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    g.draw();

    // draw sky
    glm::mat4 mm = s.calcModelMatrix();
    glm::mat4 mmvp = Perspective * stationaryView * mm;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mmvp[0][0]);
    s.draw();
}

void World::updateExploredSquares(GLFWwindow *window, glm::vec3 position, float horizontalAngle) {
    Square square((int)position[0]/5, (int)(position[2]/5));
    if (exploredSquares.find(square) == exploredSquares.end()) {
        // A new square!
        AddMoreThings(position[0], position[2], horizontalAngle);
        exploredSquares.insert(square);
        lastAdded = glfwGetTime();
    }
    for (auto it = relevantObjects.begin(); it < relevantObjects.end(); /* nothing */) {
        if (glm::length(it->rootPosition - position) < 2.0f) {
            std::cout << "Learning object at " << it->rootPosition[0] << ", "
                    << it->rootPosition[1] << ", " << it->rootPosition[2] << std::endl;
            sceneParams.moveMeans(it->params, true);
            it = relevantObjects.erase(it);
        } else {
            it++;
        }
    }
}

void World::AddMoreThings(float x, float z, float horizontalAngle) {
    glm::vec3 dirFacing(
      sin(horizontalAngle),
      0,
      cos(horizontalAngle)
    );
    int newThings = rand() % 3;
    for (int i = 0; i < newThings; i++) {
		float theta = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * MATH_FLOAT_PI * .7f) - (MATH_FLOAT_PI * .35f);
        glm::vec3 rootPos = glm::vec3(x, 0, z) + glm::rotate(glm::angleAxis(theta, glm::vec3(0, 1, 0)), dirFacing * radius);
        if ((rand() % 2) == 0) {
            TreeObject tree(rootPos, sceneParams.generate(2.0f));
            tree.init();
            allObjects.push_back(tree);
            // TODO: add support for 'growing' models.
            relevantObjects.push_back(tree);
        } else {
			RockObject rock(rootPos, glm::vec2(1.0f, 0),
				glm::vec2(- 0.5f, - .5f), glm::vec2(- 0.5f, 0.5f), sceneParams.generate(2.0f));
            rock.init();
            allObjects.push_back(rock);
            // TODO: deal with growing models here
            relevantObjects.push_back(rock);
        }
        std::cout << "Now " << relevantObjects.size() << " objects in the relevant queue" << std::endl;
    }
}
