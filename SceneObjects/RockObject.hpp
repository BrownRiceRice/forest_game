#ifndef RockObject_HPP
#define RockObject_HPP

#include <math.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include "Color.hpp"
#include "SceneObject.hpp"

#define SHADE 0.7f

namespace ParamWorld {
	class RockObject : public SceneObject{
	public:
		// Forcing it to be on the ground.
		RockObject(int depth, Color color, glm::vec3 root,
                glm::vec2 a, glm::vec2 b, glm::vec2 c, float heightMult);

	private:
		int _depth;
		float _heightMult;
		Color _color1, _color2, _color3;

		void Init(int depth, glm::vec3 a, glm::vec3 b, glm::vec3 c);

		glm::vec3 sampleInTri(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	};
}
#endif
