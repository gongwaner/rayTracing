#include "Material.h"
#include "CommonUtil.h"
#include <assert.h>


Vec3 Material::Reflect(Vec3 inDirection, Vec3 normal) const
{
    return inDirection + 2 * (-Vec3::Dot(inDirection, normal)) * normal;
}

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


Dielectric::Dielectric(double inRefractiveIndex) : refractiveIndex(inRefractiveIndex)
{
}

Vec3 Dielectric::Refract(double n1Overn2, Vec3 inDirection, Vec3 normal) const
{
    inDirection.Normalize();
    double cos_theta = Vec3::Dot(-inDirection, normal);
    assert(cos_theta < 1.0);

    Vec3 perpendicular = n1Overn2 * (cos_theta * normal + inDirection);//vector that's perpendicular to normal
    Vec3 parallel = -normal * sqrt(abs(1 - perpendicular.LengthSquared()));//vector that's parallel to normal

    //refracted ray  = perpendicular vector + parallel vector
    return perpendicular + parallel;
}

bool CanRefract(double refractionRatio, double inCosTheta)
{
    //sin_theta' = refractionRatio*sin_theta.
    //If it is > 1, this causes a total internal reflection
    double sin_theta = sqrt(1 - inCosTheta * inCosTheta);

    return refractionRatio * sin_theta <= 1.0;
}

double Schilick(double inCosTheta, double inRefractiveIndex)
{
    //Schilick's approximation for reflectance
    double vacuum_refractive_index = 1.0;//actually this should be 1.000293. for simplicity just use 1.0
    double r0 = (vacuum_refractive_index - inRefractiveIndex) / (vacuum_refractive_index + inRefractiveIndex);
    r0 *= r0;

    return r0 + (1 - r0) * pow(1 - inCosTheta, 5);
}


bool Dielectric::Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scatteredRay) const
{
    double vacuum_refractive_index = 1.0;//actually this should be 1.000293. for simplicity just use 1.0
    double refraction_ratio = record.isOutside ? vacuum_refractive_index / refractiveIndex : refractiveIndex;
    //the latter one should be refractiveIndex/vacuum_refractive_index
    //considering vacuum_refractive_index=1.0, it is abbreviated to refractiveIndex

    double cos_theta = Vec3::Dot(-inRay.GetDirection().GetUnitVector(), record.normal);
    assert(cos_theta < 1.0);

    Vec3 out_direction;
    if(CanRefract(refraction_ratio, cos_theta) ||
       Schilick(cos_theta, refractiveIndex) > GetRandomDouble())//note:in Peter Shirley's code he passed refraction_ratio as second parameter and the effect is the same
        out_direction = Refract(refraction_ratio, inRay.GetDirection(), record.normal);
    else
        out_direction = Reflect(inRay.GetDirection(), record.normal);

    scatteredRay = Ray(record.point, out_direction);
    attenuation = Colorf::White;//the glass surface absorbs nothing, so its attenuation is 1.0

    return true;
}

