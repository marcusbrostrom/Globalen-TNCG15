#pragma once

#include <glm/glm.hpp>

struct ColorDbl {
	glm::vec3 _rgb;
	
	ColorDbl():_rgb(0.0) {}

	ColorDbl(double rgb) :_rgb(rgb) {}

	ColorDbl(double r, double g, double b) //Constructor
		:_rgb(r, g, b) {}

	ColorDbl(glm::vec3 rgb):_rgb(rgb){}
};
