#pragma once

#include <glm/glm.hpp>

struct Direction {
	glm::vec3 _directionVec;


	Direction(): _directionVec(0.0){}

	Direction(double x, double y, double z) //Constructor
		:_directionVec(x, y, z) {} //Maybe normalize

	Direction(glm::vec3 direction) {
		_directionVec = glm::normalize(direction);
	}

};
