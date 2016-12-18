#ifndef TREEOBJECT_HPP
#define TREEOBJECT_HPP

#include <vector>
#include <iostream>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "../Params/AvailableParameters.h"
#include "Model.hpp"
#include "SceneObject.hpp"
#include "Color.hpp"

namespace ParamWorld {
	class TreeObject : public SceneObject {
	public:
		TreeObject(glm::vec3 root, int depth, float height, float width,
                float scale, float angle, Color leafColor, Color trunkColor, float leafSize);

		TreeObject(glm::vec3 root, float *params) :
			SceneObject(params, root),
			_depth((int)params[SP_Depth]), _height(params[SP_Height]), _width(params[SP_Width]),
			_scale(params[SP_Scale]), _splitAngle(params[SP_SplitAngle]),
			_leafColor(params[SP_LeafR], params[SP_LeafG], params[SP_LeafB]),
			_trunkColor(params[SP_BranchR], params[SP_BranchG], params[SP_BranchB]),
			_leafSize(params[SP_LeafSize])
		{
			for (int i = 0; i < SP_Count; i++) {
				printf("param[%d]: %f", i, params[i]);
			}
			printf("Depth: %d, Height: %f, ", _depth, _height);
			initModels(root, glm::vec3(_width, _height, _width), _depth,
                    glm::angleAxis(0.0f, glm::vec3(0, 1, 0)));
		}

	private:
		int _depth;
		float _height, _width, _scale, _splitAngle, _leafSize;
		Color _leafColor, _trunkColor;

		void initModels(glm::vec3 root, glm::vec3 dims, int depth, glm::fquat angleFromY);
	};
}

#endif
