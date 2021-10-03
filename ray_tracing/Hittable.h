#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class Material;

struct HitRecord
{
    Vec3 point;
    Vec3 normal;//the normal always points against the ray direction
    double t;
    bool isOutside;
    std::shared_ptr<Material> materialPtr;

    inline void SetNormal(const Ray& ray, const Vec3& outwardNormal)
    {
        isOutside = Vec3::Dot(ray.GetDirection(), outwardNormal) < 0;
        normal = isOutside ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};


#endif //HITTABLE_H
