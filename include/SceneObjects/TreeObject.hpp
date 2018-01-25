#ifndef TREEOBJECT_HPP
#define TREEOBJECT_HPP

#include <vector>
#include <iostream>
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "headers.hpp"
#include "../Params/AvailableParameters.h"
#include "Model.hpp"
#include "SceneObject.hpp"
#include "Color.hpp"
#include "../Params/ParamArray.hpp"

namespace ParamWorld {
	class TreeObject : public SceneObject {
	public:
		TreeObject(glm::vec3 root, int depth, float height, float width,
                float scale, float angle, Color leafColor, Color trunkColor, float leafSize);

		TreeObject(glm::vec3 root, ParamArray<SP_Count> params) :
			SceneObject(params, root, new Logistic(glfwGetTime() + 6.0, 1.0)),
			_depth((int)params[SP_Depth]), _height(params[SP_Height]), _width(params[SP_Width]),
			_scale(params[SP_Scale]), _splitAngle(params[SP_SplitAngle]),
			_leafColor(params[SP_LeafR], params[SP_LeafG], params[SP_LeafB]),
			_trunkColor(params[SP_BranchR], params[SP_BranchG], params[SP_BranchB]),
			_leafSize(params[SP_LeafSize])
		{
			initModels(glm::vec3(0, 0, 0), glm::vec3(_width, _height, _width), _depth,
                    glm::angleAxis(0.0f, glm::vec3(0, 1, 0)));
		}

	private:
		int _depth;
		float _height, _width, _scale, _splitAngle, _leafSize;
		Color _leafColor, _trunkColor;

		void initModels(glm::vec3 root, glm::vec3 dims, int depth, glm::fquat rotation);
	};
}

#endif
