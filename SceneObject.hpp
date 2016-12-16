#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "/usr/local/include/GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "model.hpp"

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

}



#endif
