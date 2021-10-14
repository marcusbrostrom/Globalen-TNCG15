#pragma once
#include <glm/glm.hpp>
#include <iostream>

struct Vertex {
	glm::vec3 vertex;
	float _w;

	Vertex(): vertex(0.0), _w(1.0) {}

	Vertex(float x, float y, float z, float w) //Constructor
		:vertex(x, y, z), _w(w){}

	Vertex(glm::vec3(temp))
		: vertex(temp), _w(1.0) {}

	friend std::ostream& operator<<(std::ostream& os, Vertex& dt) {



		return os << "x:" << dt.vertex.x << " y:" << dt.vertex.y << " z:" << dt.vertex.z;

	}


	Vertex operator-(Vertex rhs) {
		
		vertex -= rhs.vertex;

		return *this;

	}

	Vertex operator+(Vertex rhs) {
		
		vertex += rhs.vertex;

		return *this;

	}

	Vertex friend operator*(float rhs, Vertex temp) {

		temp.vertex.x = temp.vertex.x * rhs;
		temp.vertex.y = temp.vertex.y * rhs;
		temp.vertex.z = temp.vertex.z * rhs;


		return temp;

	}
};

