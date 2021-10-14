#pragma once
#include "Direction.h"
#include "Vertex.h"
#include "ColorDbl.h"
#include <String>

struct Ray {

	Vertex _start, _end;
	Direction _direction;
	Direction _objectNormal;
	ColorDbl _color;
	std::string _type;
	std::string _material;
	// Kanske pointer till triangel och skapa referenser till vertexpunkter

	Ray(){}


	Ray(Vertex start, Direction direction, std::string type): _start(start), _direction(direction), _type(type){}

	float getDistance() {
		return glm::distance(_start.vertex, _end.vertex);
	}

};