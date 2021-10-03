#include "Sphere.h"

//constructors
Sphere::Sphere(const Vec3& inCenter, double inRadius, std::shared_ptr<Material> inMaterialPtr)
    : center(inCenter), radius(inRadius), materialPtr(inMaterialPtr)
{
}


//setters
void Sphere::SetCenter(const Vec3& inCenter)
{
    center = inCenter;
}

void Sphere::SetRadius(double inRadius)
{
    radius = inRadius;
}


//inheritance
bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
{
    Vec3 co = ray.GetOrigin() - center;

    double a = Vec3::Dot(ray.GetDirection(), ray.GetDirection());
    double b = 2.0 * Vec3::Dot(co, ray.GetDirection());
    double c = Vec3::Dot(co, co) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    if(discriminant < 0)
        return false;

    //find the nearest root within the acceptable range
    double root = (-b - sqrt(discriminant)) / (2.0 * a);
    if(root < tMin || root > tMax)
    {
        root = (-b + sqrt(discriminant)) / (2.0 * a);

        //if none of the roots work
        if(root < tMin || root > tMax)
            return false;
    }

    //write the result to record
    record.t = root;
    record.point = ray.PointAt(record.t);
    record.materialPtr = materialPtr;

    Vec3 outward_normal = (record.point - center) / radius;//normalize
    record.SetNormal(ray, outward_normal);

    return true;
}
