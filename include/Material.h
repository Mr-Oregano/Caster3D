#pragma once

#include "Maths.h"

// Standard phong shading model.
//
struct Material
{
	Color color{ 1.0 };
	
	// NOTE: reflection counts as specular
	//
	double reflection = 0.0;
	double transmission = 0.0;
	double refractive_index = 1.0;

	double shine = 32.0;
	double diffuse = 1.0;
};