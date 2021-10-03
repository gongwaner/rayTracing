#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hittable.h"
#include "Colorf.h"


class Material
{
public:
    virtual bool Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scattered) const = 0;
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
private:
    Colorf albedo;

public:
    Metal(const Colorf& inAlbedo);

    virtual bool Scatter(const Ray& inRay, const HitRecord& record, Colorf& attenuation, Ray& scattered) const override;
};


#endif //MATERIAL_H
