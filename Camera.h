#pragma once
#include "Vertex.h"
#include "Pixel.h"
#include "Scene.h"
#include <iostream>
struct Camera {

	Vertex farview = Vertex(-1, 0, 0, 1);
	Vertex closeview = Vertex(-1, 0, 0, 1);
	glm::vec3 bottomLeftCorner{ 0, 1, 1 };
	bool moveCamera = false;
	const static int HEIGHT = 800;
	const static int WIDTH = 800;
	const double pixelSize = 0.0025;
	//Scene* scene;
	
	Pixel** pixels = new Pixel * [HEIGHT];
	//Pixel pixels[HEIGHT][WIDTH];
	

	Camera() {

		for (int i = 0; i < HEIGHT; i++) {
			pixels[i] = new Pixel[HEIGHT];
			for (int j = 0; j < WIDTH; j++) {
				pixels[i][j] = Pixel();
				
			}
		}
		/*
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				pixels[i][j] = Pixel();
			}

		}*/
			
	}

	void render(Scene& scene) {

		double StartY = bottomLeftCorner.y - pixelSize / 2;
		double StartZ = bottomLeftCorner.z - pixelSize / 2;
		glm::vec3 CP_Pixel;


		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				int counter = 0;
				CP_Pixel = glm::vec3( 0.0f, StartY - ((double)i) * pixelSize, StartZ - ((double)j) * pixelSize );
				Direction direction = Direction(CP_Pixel - farview.vertex);

				//std::cout << " Direction before: x" << direction._directionVec.x << "y" <<direction._directionVec.y << " z" << direction._directionVec.z;

				Ray r = Ray(farview, direction, "INITIAL");

				scene.CastRay(r, 0);

				pixels[j][i]._color = r._color;

			}

		}

	}

	void createImage() {
		FILE* Output = fopen("Outpuot.ppm", "wb");

		fprintf(Output, "P6\n%i %i 255\n", WIDTH, HEIGHT);

		double iMax = Imax();
		double Factor = 255.99/ iMax;

		std::cout << "Writing to file Output.ppm!!" << std::endl;
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				//std::cout << Factor << " \n";
				//std::cout << pixels[i][j]._color._rgb.x * Factor << "\n";
				fputc((int)(pixels[i][j]._color._rgb.x * Factor), Output);
				fputc((int)(pixels[i][j]._color._rgb.y * Factor), Output);
				fputc((int)(pixels[i][j]._color._rgb.z * Factor), Output);

			}

		}
		fclose(Output);
		std::cout << "Done!!" << std::endl;

	}
	double Imax() {
		double iMax = 0.0;
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {

				if (pixels[i][j]._color._rgb.x > iMax) iMax = pixels[i][j]._color._rgb.x;
				if (pixels[i][j]._color._rgb.y > iMax) iMax = pixels[i][j]._color._rgb.y;
				if (pixels[i][j]._color._rgb.z > iMax) iMax = pixels[i][j]._color._rgb.z;

			}
		}

		return iMax;
	}


};