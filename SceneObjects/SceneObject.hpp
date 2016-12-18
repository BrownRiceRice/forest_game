#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Model.hpp"
#include "Color.hpp"

namespace ParamWorld {

class SceneObject {
public:
	float *params;
	glm::vec3 rootPosition;

    void init() { m.InitBuffer(); }
	glm::mat4 calcModelMatrix();
	void draw() { m.drawBuffer(); };
	SceneObject(float *params, glm::vec3 rootPos) : params(params),
     rootPosition(rootPos) {}

protected:
    Model m;

};

class TestCube : public SceneObject {
public:
	TestCube(glm::vec3 pos);
};

// A single scene object that should just contain large swaths of a skinny box.
class Ground : public SceneObject {
public:
    Ground(float width) :
            SceneObject(nullptr, glm::vec3(0, 0, 0)) {
        m.AddBoxFromCenter(groundColor, glm::vec3(0, 0, 0),
                glm::vec3(width, 0.01f, width));
    }

private:
    const Color groundColor = Color(0.04f, 0.027f, 0.0157f);
};
}



#endif
