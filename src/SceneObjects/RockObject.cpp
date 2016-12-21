#include "RockObject.hpp"
#include <stdio.h>

using namespace ParamWorld;

// Forcing it to be on the ground.
RockObject::RockObject(int depth, Color color, glm::vec3 root,
        glm::vec2 a, glm::vec2 b, glm::vec2 c, float heightMult) :
        SceneObject(nullptr, root, new Linear(glfwGetTime(), glfwGetTime() + 5.0)),
        _depth(depth),
        _color1(color),
	    _color2(color.shiftUp(SHADE)),
        _color3(color.shiftDown(SHADE)),
        _heightMult(heightMult) {
	Init(depth, glm::vec3(a[0], 0, a[1]), glm::vec3(b[0], 0, b[1]),
            glm::vec3(c[0], 0, c[1]));
}

void RockObject::Init(int depth, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	// Select a point slightly off the triangle.
	glm::vec3 finalPt = sampleInTri(a, b, c);
	finalPt[1] = (finalPt[1] > 0) ? finalPt[1] : 0;
	// Add the tetra to the rock.
	int best = rand() % 3;
	Color *colorPtr;
	switch (best) {
	case 0:
		colorPtr = &_color1;
		break;
	case 1:
		colorPtr = &_color2;
		break;
	case 2:
		colorPtr = &_color3;
		break;
	}
    Color color = *colorPtr;
	m.AddTetra(color, finalPt, a, b, c);

	if (depth == 0) {
		return;
	}
	else {
		Init(depth - 1, finalPt, a, b);
		Init(depth - 1, finalPt, b, c);
		Init(depth - 1, finalPt, c, a);
	}
}

glm::vec3 RockObject::sampleInTri(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	float u, v;
	do {
		u = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	} while (u + v > 1);
	glm::vec3 p =  ((b - a) * u + (c - a) * v) + a;
	float w = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/_heightMult);
	glm::vec3 n = glm::cross((b - a), (c - a));
	float area = glm::length(n) / 2.0f;

	n = glm::normalize(n);

	return p + (((float)(sqrt(area) * w)) * n);
}
