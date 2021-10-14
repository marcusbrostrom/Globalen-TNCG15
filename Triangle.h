#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"
#include "Ray.h"
#include <glm/glm.hpp>
#include "Material.h"

struct Triangle {

	Vertex _p0, _p1, _p2;
	ColorDbl _color;
	Direction _normal;
	glm::vec3 _side1{ 0 }, _side2{ 0 };
	Material _material;

	
	Triangle() {}

	Triangle(Vertex p0, Vertex p1, Vertex p2, ColorDbl color, std::string material ):_p0(p0), _p1(p1), _p2(p2), _color(color)  {
		_material = Material(material);
		
		
		_side1 = _p1.vertex - _p0.vertex;
		_side2 = _p2.vertex - _p0.vertex;

		_normal = glm::normalize(glm::cross(_side1, _side2));
	

	}

	bool rayIntersection(Ray& arg, float& t_min) {
		const float EPSILON = 0.0000001;
		
		glm::vec3 h; // the normal of the ray and side 2
		glm::vec3 s; // distance from ray orgin and a corner of the triangle
		glm::vec3 q; // the normal of s and side 1

		float a, f, u, v;
		arg._direction._directionVec = glm::normalize(arg._direction._directionVec);
		h = glm::cross(arg._direction._directionVec, _side2);
		a = glm::dot(_side1, h);

		if (a > -EPSILON && a < EPSILON) return false; // Check if parallel, then false

		f = 1.0 / a;
		s = arg._start.vertex - _p0.vertex;
		u = f * glm::dot(s, h);

		if (u < 0.0 || u > 1.0) return false; // Check if ray is within triangle base

		q = glm::cross(s, _side1);
		v = f * glm::dot(arg._direction._directionVec, q);

		if (v < 0.0 || u + v > 1.0) return false; // Check if ray is within triangle height

		float t = f * glm::dot(_side2, q);

		if (t > EPSILON) {

			if (glm::distance(arg._start.vertex, arg._start.vertex + arg._direction._directionVec * t) < t_min) {
			
				
				arg._objectNormal = _normal;
				arg._end.vertex = arg._start.vertex + arg._direction._directionVec * t + 0.001f * _normal._directionVec ;
				arg._color = _color;
				arg._material = _material.material;
				t_min = arg.getDistance();
			}
			return true;

		}
		else return false;

		


		

	}
};
