#pragma once
#include "Vertex.h"
#include "Triangle.h"
#include <glm/glm.hpp>

struct Material {
	std::string material;
	Material()  {}
	Material(std::string inMaterial)  {
		material = inMaterial;
	}
	
	

};