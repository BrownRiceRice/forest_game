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
	virtual glm::mat4 calcModelMatrix() {
        return glm::translate(rootPosition);
    }
	void draw() { m.drawBuffer(); };
	SceneObject(float *params, glm::vec3 rootPos) : params(params),
     rootPosition(rootPos) {}

protected:
    Model m;
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
    const Color groundColor = Color(0.05f, 0.037f, 0.257f);
};
}



#endif
