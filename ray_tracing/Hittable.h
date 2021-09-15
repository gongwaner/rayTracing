#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

struct HitRecord
{
    Vec3 point;
    Vec3 normal;
    double t;
};

class Hittable
{
public:
    virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};


#endif //HITTABLE_H
