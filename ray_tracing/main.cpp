#include <iostream>
#include <fstream>
#include <cmath>

#include "Ray.h"
#include "Colorf.h"


Colorf GetRayColor(const Ray& r)
{
    Vec3 unit_direction = r.GetDirection().GetUnitVector();//(-1,1)
    auto t = 0.5 * (unit_direction.GetY() + 1.0);//convert (-1,1) to [0,1]

    return Colorf::SkyBlue.Lerp(Colorf::White, t);
}

void WriteColor(std::ostream& out, Colorf pixelColor)
{
    //convert from float[0.0f,1.0f] to byte[0,255]
    const float scale = 255.0f;
    out << static_cast<int>(std::round(pixelColor.GetR() * scale)) << " "
        << static_cast<int>(std::round(pixelColor.GetG() * scale)) << " "
        << static_cast<int>(std::round(pixelColor.GetB() * scale)) << "\n";
}

int main()
{
    std::ofstream out_stream;
    out_stream.open("helloWorld.ppm");

    const float aspect_ratio = 16.0f / 9.0f;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //camera
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0f;

    Vec3 origin = Vec3(0.0, 0.0, 0.0);
    Vec3 horizontal = Vec3(viewport_width, 0.0, 0.0);
    Vec3 vertical = Vec3(0.0, viewport_height, 0.0);
    Vec3 lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - Vec3(0, 0, focal_length);

    //render
    out_stream << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j)
    {
        for(int i = 0; i < image_width; ++i)
        {
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);

            Vec3 direction = lower_left_corner + (u * horizontal) + (v * vertical) - origin;
            Ray ray(origin, direction);
            Colorf pixel_color = GetRayColor(ray);
            WriteColor(out_stream, pixel_color);
        }
    }

    out_stream.close();
}
