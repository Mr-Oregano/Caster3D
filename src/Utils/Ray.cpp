
#include "Ray.h"

Ray::Ray(Vec3 origin, Vec3 dir)
	: origin(origin), dir(dir)
{}

Vec3 Ray::GetPoint(double distance) const
{
	return origin + distance * dir;
}
