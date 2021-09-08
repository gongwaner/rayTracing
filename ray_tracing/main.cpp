#include <iostream>
#include <fstream>
#include <cmath>

#include "Colorf.h"


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

    const int image_width = 800;
    const int image_height = 600;

    //render
    out_stream << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j)
    {
        for(int i = 0; i < image_width; ++i)
        {
            Colorf pixel_color = Colorf(float(i) / (image_width - 1), float(j) / (image_height - 1), 0.25f);
            WriteColor(out_stream,pixel_color);
        }
    }

    out_stream.close();
}
