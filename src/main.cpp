#include "color.h"
#include "vec3.h"
#include <iostream>

int main()
{
    int imageWidth = 260;
    int imageHeight = 260;
    // PPM Description
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++)
    {
        for (int i = 0; i < imageWidth; i++)
        {
            auto pixel_color = color(double(i)/(imageWidth-1), double(j)/(imageHeight-1), 0);
            write_color(std::cout, pixel_color);

        }
    }

    return 0;
}