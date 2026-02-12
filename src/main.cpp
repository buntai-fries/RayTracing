#include "color.h"
#include "vec3.h"
#include "ray.h"
#include <iostream>

color ray_color(const ray& r) {
    vec3 unitDirection = unit_vector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    int imageWidth = 400;
    auto aspectRatio = 16.0/9.0;
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;
    // Setting Camera
    auto viewportWidth = 2.0;
    auto focalLength = 1.0;
    auto viewportHeight = viewportWidth * (double(imageWidth)/imageHeight);
    auto cameraCenter = point3(0, 0, 0);
    // Calculate the vector across vertically and horizontally
    auto viewport_u = vec3(viewportWidth, 0, 0);
    auto viewport_v = vec3(0, -viewportHeight, 0);
    // Calculate the delta vector across x and y from pixel-pixel
    auto viewport_del_u = viewport_u / imageWidth;
    auto viewport_del_v = viewport_v / imageHeight;
    // Calculate the location of the upper left pixel
    auto viewUpperLeft = cameraCenter - 
                         vec3(0, 0, focalLength) - 
                         viewport_u/2 - 
                         viewport_v/2;
    auto pixelLoc = viewUpperLeft + 0.5*(viewport_del_u + viewport_del_v);

    std::cout << "P3" << "\n" << imageWidth << " " << 
    imageHeight << "\n" << "255" << std::endl;

    for (int j = 0; j < imageHeight; j++) {
        for (int i = 0; i < imageWidth; i++) {
            auto pixelCenter = pixelLoc + (i * viewport_del_u) + (j * viewport_del_v);
            auto rayDirection = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDirection);
            auto pixelColor = ray_color(r);
            write_color(std::cout, pixelColor);
        }
    }

    return 0;
}