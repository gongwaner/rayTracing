#ifndef COMMONUTIL_H
#define COMMONUTIL_H

#include <random>


/**
 * return random number in [0,1)
 */
inline double GetRandomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;

    return distribution(generator);
}

/**
 * return random number in [min,max)
 */
inline double GetRandomDouble(double min, double max)
{
    return min + (max - min) * GetRandomDouble();
}

inline Vec3 GetRandomVector()
{
    return Vec3(GetRandomDouble(), GetRandomDouble(), GetRandomDouble());
}

inline Vec3 GetRandomVector(double min, double max)
{
    return Vec3(GetRandomDouble(min, max), GetRandomDouble(min, max), GetRandomDouble(min, max));
}

/**
 * rejection method to pick a random point in unit sphere(r=1)
 * pick a random point in the unit cube where x, y, and z all range from −1 to +1.
 * Reject this point and try again if the point is outside the sphere.
 */
inline Vec3 GetRandomVectorInUnitSphere()
{
    while(true)
    {
        Vec3 p = GetRandomVector(-1, 1);
        if(p.LengthSquared() >= 1)
            continue;

        return p;
    }
}

inline Vec3 GetLambertianRandomUnitVector()
{
    return GetRandomVectorInUnitSphere().GetUnitVector();
}

inline Colorf GetNormalColor(const HitRecord& record)
{
    return Colorf(float(0.5 * record.normal.GetX() + 0.5), float(0.5 * record.normal.GetY() + 0.5),
                  float(0.5 * record.normal.GetZ() + 0.5));//convert (-1,1) to [0,1]
}

inline Colorf GetBackgroundColor(const Ray& ray)
{
    Vec3 unit_direction = ray.GetDirection().GetUnitVector();//(-1,1)
    auto t = 0.5 * unit_direction.GetY() + 0.5;//convert (-1,1) to [0,1]

    return Colorf::SkyBlue.Lerp(Colorf::White, t);
}

inline bool HitAnything(const Ray& ray, double tmin, double tmax, HitRecord& record,
                        const std::vector<std::unique_ptr<Hittable>>& objects)
{
    HitRecord temp_record;
    bool hit_anything = false;
    double closest_so_far = tmax;

    for(const auto& object:objects)
    {
        if(object->Hit(ray, tmin, closest_so_far, temp_record))
        {
            hit_anything = true;
            record = temp_record;
            closest_so_far = temp_record.t;
        }
    }

    return hit_anything;
}


#endif //COMMONUTIL_H
