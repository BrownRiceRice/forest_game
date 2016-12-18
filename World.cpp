#include "World.hpp"
#include <iostream>

using namespace ParamWorld;

World::World(float worldExtent, GLuint matID) :
        sceneParams(),
        g(Ground(worldExtent)),
        MatrixID(matID) {
    g.init();
}

void World::Render(glm::mat4 Perspective, glm::mat4 View) {
    for (auto it = worldObjects.begin(); it != worldObjects.end(); it++) {
        glm::mat4 ModelM = it->calcModelMatrix();
        glm::mat4 mvp = Perspective * View * ModelM;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        it->draw();
    }
    // draw ground
    glm::mat4 ModelM = g.calcModelMatrix();
    glm::mat4 mvp = Perspective = Perspective * View * ModelM;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    g.draw();
}

void World::updateExploredSquares(glm::vec3 position, float horizontalAngle) {
    Square square((int)position[0]/5, (int)(position[2]/5));
    if (exploredSquares.find(square) == exploredSquares.end()) {
        // A new square!
        AddMoreThings(position[0], position[2], horizontalAngle);
        exploredSquares.insert(square);
    }
}

void World::AddMoreThings(float x, float z, float horizontalAngle) {
    std::cout << "Number of objects in the world: " << worldObjects.size() << std::endl;
    int newThings = rand() % 3;
    for (int i = 0; i < newThings; i++) {
		float theta = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * MATH_FLOAT_PI * .7f) - (MATH_FLOAT_PI * .35f);
        glm::vec3 dirFacing(
            sin(horizontalAngle),
            0,
            cos(horizontalAngle)
        );
        glm::vec3 rootPos = glm::vec3(x, 0, z) + glm::rotate(glm::angleAxis(theta, glm::vec3(0, 1, 0)), dirFacing * radius);
        if ((rand() % 2) == 0) {
            TreeObject tree(rootPos, sceneParams.generate(2.0f));
            tree.init();
            worldObjects.push_back(tree);
            // TODO: add support for 'growing' models.
            // TODO: add support for 'relevant' models.
        } else {
			RockObject rock(4, Color(.8, .9, .75), rootPos, glm::vec2(rootPos.x + 1.0f, rootPos.z),
				glm::vec2(rootPos.x - 0.5f, rootPos.z - .5f), glm::vec2(rootPos.x - 0.5f, rootPos.z + 0.5f), 1.4f);
            rock.init();
            worldObjects.push_back(rock);
            // TODO: deal with growing models here
        }
    }
}
