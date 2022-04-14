#pragma once

#include "Maths.h"

// Standard phong shading model.
//
struct Material
{
	Color specular{ 1.0 };
	Color diffuse{ 1.0 };
	Color ambient{ 0.0 };
	
	// NOTE: reflection counts as specular
	//
	double reflection = 0.0;
	double transmissivity = 0.0;
	double refractive_index = 1.0;

	double shine = 32.0;
};