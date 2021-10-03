#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hittable.h"
#include "Colorf.h"


class Material
{
public:
    virtual bool Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scatteredRay) const = 0;
};


class Lambertian : public Material
{
private:
    Colorf albedo;

public:
    Lambertian(const Colorf& inAlbedo);

    virtual bool Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scattered) const override;
};


class Metal : public Material
{
protected:
    Colorf albedo;

public:
    Metal(const Colorf& inAlbedo);

    Vec3 Reflect(Vec3 inDirection, Vec3 normal) const;
    virtual bool Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scatteredRay) const override;
};


class FuzzyMetal : public Metal
{
    double fuzziness;

public:
    FuzzyMetal(const Colorf& inAlbedo, double inFuzziness);

    virtual bool Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scatteredRay) const override;

};


class Dielectric : public Material
{
    double refractiveIndex;//n=c/v

public:
    Dielectric(double inRefractiveIndex);

    Vec3 Refract(double etaiOverEtat, Vec3 inDirection, Vec3 normal) const;
    virtual bool Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scatteredRay) const override;
};


#endif //MATERIAL_H
