#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"


class Sphere : public Hittable
{
private:
    Vec3 center;
    double radius;
    std::shared_ptr<Material> materialPtr;

public:
    //constructors
    Sphere() = default;
    Sphere(const Vec3& inCenter, double inRadius, std::shared_ptr<Material> inMaterialPtr);


    //getter and setters
    Vec3 GetCenter() const      { return center; }
    double GetRadius() const    { return radius; }

    void SetCenter(const Vec3& inCenter);
    void SetRadius(double inRadius);


    //inheritance
    virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
};


#endif //SPHERE_H
