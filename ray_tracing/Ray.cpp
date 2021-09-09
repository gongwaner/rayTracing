#include "Ray.h"

//constructor
Ray::Ray(const Vec3& inOrigin, const Vec3& inDirection) : origin(inOrigin), direction(inDirection)
{
}


//utility functions
Vec3 Ray::PointAt(double t) const
{
    return origin + t * direction;
}
