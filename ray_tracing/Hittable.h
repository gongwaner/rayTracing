#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

struct HitRecord
{
    Vec3 point;
    Vec3 normal;//the normal always points against the ray direction
    double t;
    bool is_outside;

    inline void SetNormal(const Ray& ray, const Vec3& outwardNormal)
    {
        is_outside = Vec3::Dot(ray.GetDirection(), outwardNormal) < 0;
        normal = is_outside ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};


#endif //HITTABLE_H
