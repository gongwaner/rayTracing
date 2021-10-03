#include "Material.h"
#include "CommonUtil.h"


Lambertian::Lambertian(const Colorf& inAlbedo) : albedo(inAlbedo)
{
}

bool Lambertian::Scatter(const Ray& ray, const HitRecord& record, Colorf& attenuation, Ray& scatteredRay) const
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
