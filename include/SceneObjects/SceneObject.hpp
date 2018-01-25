#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "headers.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Model.hpp"
#include "Color.hpp"
#include "Function.hpp"
#include "../Params/ParamArray.hpp"
#include "../Params/AvailableParameters.h"

namespace ParamWorld {

class SceneObject {
public:
	ParamArray<SP_Count> params;
	glm::vec3 rootPosition;

    void init() { m.InitBuffer(); }
	virtual glm::mat4 calcModelMatrix() {
        double sizeNow = size->at(glfwGetTime());
        return glm::translate(rootPosition) * glm::scale(glm::mat4(1.0f), glm::vec3(sizeNow, sizeNow, sizeNow));
    }
	void draw() { m.drawBuffer(); };
	SceneObject(ParamArray<SP_Count> params, glm::vec3 rootPos, Function *f) : params(params), size(f),
      rootPosition(rootPos) {}
	SceneObject(ParamArray<SP_Count> params, glm::vec3 rootPos) : params(params), size(new Constant()),
      rootPosition(rootPos) {
         //Constant c;
         //size = c;
     }

protected:
    Model m;

private:
    Function *size;
};

// A single scene object that should just contain large swaths of a skinny box.
class Ground : public SceneObject {
public:
    Ground(float width) :
            SceneObject(ParamArray<SP_Count>(), glm::vec3(0, 0, 0)) {
        m.AddBoxFromCenter(groundColor, glm::vec3(0, 0, 0),
                glm::vec3(width, 0.01f, width));
    }

private:
    const Color groundColor = Color(0.05f, 0.037f, 0.257f);
};
}



#endif
