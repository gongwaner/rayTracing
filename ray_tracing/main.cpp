#include <iostream>
#include <fstream>

#include "Ray.h"
#include "Colorf.h"
#include "Sphere.h"
#include "Camera.h"
#include "CommonUtil.h"
#include "Material.h"


Colorf GetNormalColor(const HitRecord& record)
{
    return Colorf(float(0.5 * record.normal.GetX() + 0.5), float(0.5 * record.normal.GetY() + 0.5),
                  float(0.5 * record.normal.GetZ() + 0.5));//convert (-1,1) to [0,1]
}

Colorf GetBackgroundColor(const Ray& ray)
{
    Vec3 unit_direction = ray.GetDirection().GetUnitVector();//(-1,1)
    auto t = 0.5 * unit_direction.GetY() + 0.5;//convert (-1,1) to [0,1]

    return Colorf::SkyBlue.Lerp(Colorf::White, t);
}

bool HitAnything(const Ray& ray, double tmin, double tmax, HitRecord& record,
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


Colorf GetRayColor(const Ray& ray, const std::vector<std::unique_ptr<Hittable>>& objects, int maxItr = 10)
{
    //exceed ray bounce limit, no more light is gathered
    if(maxItr <= 0)
        return Colorf::Black;

    HitRecord record;
    if(HitAnything(ray, 0.0001, std::numeric_limits<double>::infinity(), record, objects))
    {
        Ray scattered_ray;
        Colorf attenuation;

        if(record.materialPtr->Scatter(ray, record, attenuation, scattered_ray))
            return attenuation * GetRayColor(scattered_ray, objects, --maxItr);

        return Colorf::Black;
    }

    return GetBackgroundColor(ray);
}


int main()
{
    std::ofstream out_stream;
    out_stream.open("helloWorld.ppm");

    const float aspect_ratio = 16.0f / 9.0f;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_iter = 20;

    //camera
    Vec3 look_from(-2, 2, 1);
    Vec3 look_at(0, 0, -1);
    Vec3 up(0, 1, 0);
    Camera camera(look_from, look_at, up, 90.0, aspect_ratio);

    //objects
    auto material_ground = std::make_shared<Lambertian>(Colorf(0.564f, 0.827f, 0.996f));
    auto material_metal_grey = std::make_shared<Metal>(Colorf(0.8f, 0.8f, 0.8f));
    auto material_dielectric_glass = std::make_shared<Dielectric>(1.5);
    auto material_lambert_pink = std::make_shared<Lambertian>(Colorf(0.7f, 0.3f, 0.3f));


    std::vector<std::unique_ptr<Hittable>> objects;
    objects.push_back(std::make_unique<Sphere>(Vec3(0.0, -100.5, -1.0), 100, material_ground));//ground

    objects.push_back(std::make_unique<Sphere>(Vec3(-1.0, 0.0, -1.5), 0.5, material_metal_grey));
    objects.push_back(std::make_unique<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5, material_dielectric_glass));
    objects.push_back(std::make_unique<Sphere>(Vec3(1.0, 0.0, -2.0), 0.5, material_lambert_pink));
    objects.push_back(std::make_unique<Sphere>(Vec3(1.5, 0.0, -1.6), -0.4, material_dielectric_glass));//trick:giving negative radius yields hollow sphere(aka.bubble)


    //render
    out_stream << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j)
    {
        for(int i = 0; i < image_width; ++i)
        {
            //for each pixel, send multiple rays and average it
            Colorf pixel_color = Colorf(0.0f, 0.0f, 0.0f);
            for(int itr = 0; itr < samples_per_pixel; ++itr)
            {
                double u = double(i + GetRandomDouble()) / (image_width - 1);
                double v = double(j + GetRandomDouble()) / (image_height - 1);

                pixel_color += GetRayColor(camera.GetRay(u, v), objects, max_iter);
            }
            WriteColorMultiSample(out_stream, pixel_color, samples_per_pixel);
        }
    }

    out_stream.close();
}
