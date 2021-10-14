#pragma once
#include "Vertex.h"
#include "Triangle.h"
#include <glm/glm.hpp>

struct Light {
	Light() {}
	float x = 7.0;
	float y = 0.0;
	float z = 4.9;

	/*double x = 7.0;
	double y = -5.99;
	double z = 0;*/
	Vertex centrum = Vertex(x, y, z, 1.0);
	std::string LIGHT = "LIGHT";
	Direction _normal = Direction (0.0f,0.0f,-1.0f);
	Vertex vertices[4]{
	Vertex(x-1, y+1, z, 1.0), //p0
	Vertex(x-1, y-1, z, 1.0), //p1
	Vertex(x+1, y+1, z, 1.0), //p2
	Vertex(x+1, y-1, z, 1.0), //p3
	//Vertex(x-1, y, z+1, 1.0), //p0
	//Vertex(x-1, y, z-1, 1.0), //p1
	//Vertex(x+1, y, z+1, 1.0), //p2
	//Vertex(x+1, y, z-1, 1.0), //p3


	};
	ColorDbl color{ 1.0, 1.0, 1.0 };

	Triangle triangles[2]{

		//Floor
		Triangle(vertices[0], vertices[2], vertices[1], color, LIGHT),
		Triangle(vertices[1],vertices[2], vertices[3], color, LIGHT),
		
	};

};