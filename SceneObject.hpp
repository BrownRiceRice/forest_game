#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "/usr/local/include/GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace ParamWorld {

class SceneObject {
public:
		float *params;
		glm::vec3 rootPosition;
		virtual void InitBuffer()=0;
		virtual glm::mat4 calcModelMatrix()=0;
		virtual void drawBuffer()=0;
		SceneObject(float *params, glm::vec3 rootPos) : params(params), rootPosition(rootPos) {}

};

class TestCube : SceneObject {
public:
	  TestCube(glm::vec3 pos): SceneObject(nullptr, pos) {}

    void InitBuffer();
		glm::mat4 calcModelMatrix();
		void drawBuffer();

//private:
    GLuint vertexbuffer, colorbuffer;
};

}



#endif
