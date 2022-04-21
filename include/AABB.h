#pragma once

#include "Maths.h"

// Axis aligned bounding box 
// for use with BVH

struct AABB
{
	Vec3 bl;
	Vec3 tr;
};