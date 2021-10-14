#pragma once
#include "Vertex.h"
#include "Tetrahedron.h"
#include "Sphere.h"

#include "Light.h"

#include "Triangle.h"
#include <glm/glm.hpp>
#include <random>
std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
struct Scene {
	
	Scene() {}

	

	ColorDbl red{ 1.0, 0.0, 0.0 };
	ColorDbl green{ 0.0, 1.0, 0.0 };
	ColorDbl blue{ 0.0, 0.0, 1.0 };
	ColorDbl yellow{ 1.0, 1.0, 0.0 };
	ColorDbl pink{ 1.0, 0.08, 0.6 };
	ColorDbl gray{ 0.5, 0.5, 0.5 };
	ColorDbl turquoise{ 0.5, 1.0, 1.0 };
	ColorDbl white{ 1.0, 1.0, 1.0 };

	//Tetrahedron tetra;
	Vertex temp = Vertex{ 8.0, 0.0, 0.0, 1.0 };
	Vertex temp2 = Vertex{ 8.0, 0.0, -3.0, 1.0 };
	Sphere sphere = Sphere{ 1.0, temp, turquoise, "LAMBERTIAN" };
	Sphere sphere2 = Sphere{ 2.0, temp2, green, "LAMBERTIAN" };
	Light light;
	
	std::string LAMBERTIAN = "LAMBERTIAN";


	Vertex vertices[12]{

		//floor vertices
		Vertex(-3.0, 0.0, -5.0, 1.0), //p0
		Vertex(0.0, 6.0, -5.0, 1.0), //p1
		Vertex(10.0, 6.0, -5.0, 1.0), //p2
		Vertex(13.0, 0.0, -5.0, 1.0), //p3
		Vertex(10.0, -6.0, -5.0, 1.0), //p4
		Vertex(0.0, -6.0, -5.0, 1.0), //p5

		//roof vertices
		Vertex(-3.0, 0.0, 5.0, 1.0), //p6
		Vertex(0.0, 6.0, 5.0, 1.0), //p7
		Vertex(10.0, 6.0, 5.0, 1.0), //p8
		Vertex(13.0, 0.0, 5.0, 1.0), //p9
		Vertex(10.0, -6.0, 5.0, 1.0), //p10
		Vertex(0.0, -6.0, 5.0, 1.0), //p11


	};


	Triangle triangles[24]{

		//Floor
		Triangle(vertices[0], vertices[5], vertices[1], yellow, LAMBERTIAN),
		Triangle(vertices[1],vertices[5], vertices[4], yellow, LAMBERTIAN),
		Triangle(vertices[1],vertices[4], vertices[2], yellow, LAMBERTIAN),
		Triangle(vertices[2],vertices[4], vertices[3], yellow, LAMBERTIAN),

		//Roof
		Triangle(vertices[6], vertices[7], vertices[11], green, LAMBERTIAN),
		Triangle(vertices[7],vertices[10], vertices[11], green, LAMBERTIAN),
		Triangle(vertices[7],vertices[8], vertices[10], green, LAMBERTIAN),
		Triangle(vertices[8],vertices[9], vertices[10], green, LAMBERTIAN),

		//Wall 1
		Triangle(vertices[0], vertices[6], vertices[5], yellow, LAMBERTIAN),
		Triangle(vertices[5],vertices[6], vertices[11], yellow, LAMBERTIAN),

		//Wall 2
		Triangle(vertices[4], vertices[5], vertices[11], red, LAMBERTIAN),
		Triangle(vertices[4],vertices[11], vertices[10], red, LAMBERTIAN),

		//Wall 3
		Triangle(vertices[4], vertices[10], vertices[9], blue, LAMBERTIAN),
		Triangle(vertices[3],vertices[4], vertices[9], blue, LAMBERTIAN),

		//Wall 4
		Triangle(vertices[3], vertices[9], vertices[2], white, LAMBERTIAN),
		Triangle(vertices[2],vertices[9], vertices[8], white, LAMBERTIAN),

		//Wall 5
		Triangle(vertices[8], vertices[1], vertices[2], pink, LAMBERTIAN),
		Triangle(vertices[1],vertices[8], vertices[7], pink, LAMBERTIAN),

		//Wall 6
		Triangle(vertices[7], vertices[0], vertices[1], turquoise, LAMBERTIAN),
		Triangle(vertices[7],vertices[6], vertices[0], turquoise, LAMBERTIAN),

		//Light
		light.triangles[0],
		light.triangles[1],
	
	};

	void CastRay(Ray& arg, int depth) {
		
		arg._color = ColorDbl(0.0f, 0.0f, 0.0f);
		//if(depth < 1) return;
				float t_min = 1000;

		sphere.rayIntersection(arg, t_min);
		sphere2.rayIntersection(arg, t_min);

		for (int g = 0; g < 24; g++) {	 
			triangles[g].rayIntersection(arg, t_min);
		}
		//tetra.rayIntersection(arg, t_min);

		
		
		if(arg._material == "LIGHT"){
		//	std::cout << "ISSA SHADOW";

			return;
		}
		if (arg._type == "SHADOW") {
			return;
		}

	
		if (arg._material == "LAMBERTIAN") {
			ColorDbl directLight = DirectLight(arg);

			arg._color._rgb = directLight._rgb;
		
			
		}
		return;


	}

	ColorDbl DirectLight(Ray& arg) {
		ColorDbl directLight = ColorDbl(0.0f, 0.0f, 0.0f); 

		Vertex v0 = Vertex(0.0f, 0.0f, 0.0f, 1.0);
		Vertex v1 = Vertex(0.0f, 1.0f, 0.0f, 1.0);
		Vertex v2 = Vertex(1.0f, 0.0f, 0.0f, 1.0);
		Vertex v3 = Vertex(1.0f, 1.0f, 0.0f, 1.0);

		int numberOfShadowRays = 3;
		
		for (int i = 0; i < numberOfShadowRays; i++) {

			float u = distribution(generator);
			float v = distribution(generator);
			Vertex qi = Vertex(u * (v1.vertex - v0.vertex) + v * (v2.vertex - v0.vertex));
			qi = qi + Vertex(light.x,light.y,4.8f, 1.0);
		
			Direction rayDirection = qi.vertex - arg._end.vertex;
			float distanceLength = glm::distance(arg._end.vertex, qi.vertex);
			float rounded_upDist = ceilf(distanceLength * 100) / 100;

			float cos_alpha = glm::max(0.0f, glm::dot(-rayDirection._directionVec, light._normal._directionVec));
			float cos_beta = glm::max(0.0f, glm::dot(rayDirection._directionVec, arg._objectNormal._directionVec));

			rayDirection = glm::normalize(rayDirection._directionVec);
			Ray shadowRay = Ray(arg._end, rayDirection, "SHADOW");
			Ray tempRay = shadowRay;
			CastRay(shadowRay, 0);
			if (tempRay.getDistance() != shadowRay.getDistance()) {
				std::cout << "EEEEE: " << tempRay.getDistance() << "\n";
				std::cout << "wwwww: " << shadowRay.getDistance() << "\n";


			}
			float shadowRayLength = glm::distance(shadowRay._start.vertex, shadowRay._end.vertex);
			float rounded_upShad = ceilf(distanceLength * 100) / 100;
			if (rounded_upShad < rounded_upDist) {
				//std::cout << "ShadowLength: " << rounded_upShad << std::endl << " distanceLength: " << rounded_upDist << std::endl;

			}

			else {
				directLight._rgb +=  arg._color._rgb * (cos_alpha * cos_beta / (distanceLength * distanceLength));
				//std::cout << "DirectLigt: r" << directLight._rgb.r << " g " << directLight._rgb.g << " b " << directLight._rgb.b; 
				

			} 
			
		}
		float A = glm::length(glm::cross(v1.vertex - v0.vertex, v3.vertex - v0.vertex));
		return (30*A*directLight._rgb/(float)numberOfShadowRays);

		
		

		

		


	}
	



	

};
