#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include "Ray.h"
#include "Material.h"
struct Sphere
{
	float _radius = 0;
	Vertex _position;
	ColorDbl _color;
	Material _material;
	Sphere() {
		
	}
	
	Sphere(float radius, Vertex position, ColorDbl color, std::string material) {

		_radius = radius;
		_position.vertex = position.vertex;
		_color._rgb = color._rgb;
		_material.material = material;

	}
	

	bool rayIntersection(Ray& arg, float& t_min) {
		const float EPSILON = 0.0000001;

		glm::vec3 L = _position.vertex - arg._start.vertex;

		float tca = glm::dot(L, arg._direction._directionVec);

		if (tca < EPSILON) {
			return false;
		}

		float d = sqrt(glm::dot(L, L) - pow(tca, 2)); 

		if (d > _radius) {
			return false;
		}

		float thc = sqrt(pow(_radius, 2) - pow(d, 2));

		float t0 = tca - thc;
		float t1 = tca + thc;

		if (t0 > t1) {
			std::swap(t0, t1);
		}

		if (t0 < EPSILON) {
			t0 = t1;
			if (t0 < EPSILON) return false;

		}

		if (glm::distance(arg._start.vertex, arg._start.vertex + arg._direction._directionVec * t0) < t_min) {
			

			Vertex intersection = arg._start.vertex + arg._direction._directionVec * t0;
			
			Direction normal = glm::normalize(intersection.vertex - _position.vertex);
			arg._objectNormal = normal;
			arg._end.vertex = intersection.vertex + normal._directionVec * 0.001f;
			arg._color = _color;
			arg._material = _material.material;
			t_min = arg.getDistance();
		}

		return true;

	}

	

	

};
