#include <iostream>
#include <fstream>

#include "Ray.h"
#include "Colorf.h"
#include "Sphere.h"
#include "Camera.h"
#include "CommonUtil.h"
#include "Material.h"


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
    Camera camera;

    //objects
    auto material_center = std::make_shared<Lambertian>(Colorf(0.7f, 0.3f, 0.3f));
    auto material_ground = std::make_shared<Lambertian>(Colorf(0.8f, 0.8f, 0.0f));
    auto material_left = std::make_shared<Metal>(Colorf(0.8f, 0.8f, 0.8f));
    auto material_right = std::make_shared<FuzzyMetal>(Colorf(0.8f, 0.6f, 0.2f), 1.0);

    std::vector<std::unique_ptr<Hittable>> objects;
    objects.push_back(std::make_unique<Sphere>(Vec3(0.0, -100.5, -1.0), 100, material_ground));//ground

    objects.push_back(std::make_unique<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.5, material_left));
    objects.push_back(std::make_unique<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5, material_center));
    objects.push_back(std::make_unique<Sphere>(Vec3(1.0, 0.0, -1.0), 0.5, material_right));

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
