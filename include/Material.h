#pragma once

#include "Maths.h"

// Standard phong shading model.
//
struct Material
{
	Color color{ 1.0 };
	double reflection = 0.0;
	double shine = 32.0;
	double diffuse = 1.0;
	double specular = 1.0;
};