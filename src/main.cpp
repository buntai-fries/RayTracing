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
            auto r = double(i)/(imageWidth-1);
            auto g = double(j)/(imageHeight-1);
            auto b = 0.0;

            int ir = int(255.999*r);
            int ig = int(255.999*g);
            int ib = int(255.999*b);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}