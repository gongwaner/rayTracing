#ifndef RAY_H
#define RAY_H

#include "Vec3.h"


class Ray
{
private:
    Vec3 origin;
    Vec3 direction;

public:
    //constructors
    Ray(const Vec3& inOrigin, const Vec3& inDirection);


    //getter
    Vec3 GetOrigin() const      { return origin; }
    Vec3 GetDirection() const   { return direction; }


    //utility functions
    Vec3 PointAt(double t) const;
};


#endif //RAY_H
