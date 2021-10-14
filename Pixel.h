#pragma once
#include "Direction.h"
#include "Vertex.h"
#include "ColorDbl.h"
#include "Ray.h"


struct Pixel {
	ColorDbl _color;
	//Ray& _ray; //Oklart om detta stämmer

	Pixel() :_color(0.5) {}
	Pixel(ColorDbl color) : _color{ color } {}

	Pixel operator=(ColorDbl input) {
		_color._rgb.r = input._rgb.r;
		_color._rgb.g = input._rgb.g;
		_color._rgb.b = input._rgb.b;

	}
};