#include "Material.h"
#include "CommonUtil.h"


Lambertian::Lambertian(const Colorf& inAlbedo) : albedo(inAlbedo)
{
}

bool Lambertian::Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scatteredRay) const
{
    Vec3 scatter_direction = record.normal + GetLambertianRandomUnitVector();

    //we don't want 0 scatter direction vector
    //which will lead to infinity and NAN
    if(scatter_direction.EpsilonEqual(0.0, 1e-8))
        scatter_direction = record.normal;

    scatteredRay = Ray(record.point, scatter_direction);
    attenuation = albedo;

    return true;
}


Metal::Metal(const Colorf& inAlbedo) : albedo(inAlbedo)
{
}

Vec3 Metal::Reflect(Vec3 inDirection, Vec3 normal) const
{
    return inDirection + 2 * (-Vec3::Dot(inDirection, normal)) * normal;
}

bool Metal::Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scatteredRay) const
{
    Vec3 scatter_direction = Reflect(inRay.GetDirection(), record.normal);
    scatteredRay = Ray(record.point, scatter_direction);
    attenuation = albedo;

    //only when scattered ray is on the horizontal level will light be scattered
    return Vec3::Dot(scatteredRay.GetDirection(), record.normal) > 0;
}

FuzzyMetal::FuzzyMetal(const Colorf& inAlbedo, double inFuzziness) : Metal(inAlbedo), fuzziness(inFuzziness < 1.0 ? inFuzziness : 1.0)
{
}

bool FuzzyMetal::Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scatteredRay) const
{
    Vec3 scatter_direction = Reflect(inRay.GetDirection(), record.normal);
    scatteredRay = Ray(record.point, scatter_direction + fuzziness * GetRandomVectorInUnitSphere());
    attenuation = albedo;

    //only when scattered ray is on the horizontal level will light be scattered
    return Vec3::Dot(scatteredRay.GetDirection(), record.normal) > 0;
}
