#include "TreeObject.h"

#define MATH_FLOAT_PI (float) 3.1415926

using namespace ParamWorld;

TreeObject::TreeObject(glm::vec3 root, int depth, float height, float width,
	float scale, float angle, Color leafColor,
	Color trunkColor, float leafSize) :
	SceneObject(nullptr, root),
	_depth(depth),
	_height(height),
	_width(width),
	_scale(scale),
	_splitAngle(angle),
	_leafColor(leafColor),
	_trunkColor(trunkColor),
	_leafSize(leafSize)
{
	initModels(root, glm::vec3(width, height, width), depth, glm::fquat(1.0, 0.0, 0.0, 0.0));
}

void TreeObject::initModels(glm::vec3 root, glm::vec3 dims, int depth, glm::fquat angleFromY) {
	if (depth == 0) {
		// Add one cube, the leaf color. Dimensions should be all the width, I guess.
		m.AddBoxFromCenter(_leafColor, root + glm::rotate(angleFromY,
                glm::vec3(0, dims.x, 0)),
                glm::vec3(dims[1] * 2, dims[0] * 2, dims[1] * 2),
                angleFromY);
	}
	else {
		glm::vec3 newZ = glm::rotate(angleFromY, glm::vec3(0, 0, 1));
		glm::vec3 newY = glm::rotate(angleFromY, glm::vec3(0, 1, 0));
		//Quatf left = Quatf((Quatf(newZ, _splitAngle) * angleFromY) , 0); // MATH_FLOAT_PI / 2);
        glm::vec3 temp = glm::rotate(angleFromY, glm::vec3(0, dims[1] / 2.0, 0));
		m.AddBoxFromCenter(_trunkColor, root + glm::rotate(angleFromY, glm::vec3(0, dims[1] / 2, 0)), dims, angleFromY);
		glm::fquat left = glm::angleAxis(_splitAngle, newZ) * glm::angleAxis(MATH_FLOAT_PI/2.0f, newY) * angleFromY;
		glm::fquat right = glm::angleAxis(-_splitAngle, newZ) * glm::angleAxis(-MATH_FLOAT_PI/2.0f, newY) * angleFromY;
		glm::vec3 newRoot = root + glm::rotate(angleFromY, glm::vec3(0, dims[1], 0));
		initModels(newRoot, dims * _scale, depth - 1, left);
		initModels(newRoot, dims * _scale, depth - 1, right);
	}
}
