#pragma once


#include "Vertex.h"
#include "Triangle.h"
#include <glm/glm.hpp>

struct Tetrahedron {
	Tetrahedron() {}

	Vertex vertices[4]{
	Vertex(6.0, 0.0, 1.0, 1.0), //v0
	Vertex(5.0, -1.0, -1.0, 1.0), //v1
	Vertex(5.0, 1.0, -1.0, 1.0), //v2
	Vertex(5.0, 0.0, -1.0, 1.0), //p3

	

	};
	ColorDbl color{ 1.0, 1.0, 0.0 };
	std::string LAMBERTIAN = "LAMBERTIAN";
	Triangle triangles[4]{

		//Floor
		Triangle(vertices[1], vertices[2], vertices[3], color, LAMBERTIAN),
		Triangle(vertices[1],vertices[3], vertices[0], color, LAMBERTIAN),
		Triangle(vertices[0],vertices[3], vertices[2], color, LAMBERTIAN),
		Triangle(vertices[0],vertices[2], vertices[1], color, LAMBERTIAN),
	};

	bool rayIntersection(Ray& arg, float& t_min) {

		
		for (int g = 0; g < 4; g++) {
			triangles[g].rayIntersection(arg, t_min);	
		}	
		return false;
		
	}


	
//Färg

//Vertex

//Triangle


};

