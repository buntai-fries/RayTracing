# RayTracing Project

The project follows the standard structure for a Ray Tracing in One Weekend implementation, ideal for C++ with CMake on Fedora Linux. [realtimerendering](https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf)

```
RayTracingMain/
├── render.sh
└── RayTracing/
    ├── src/
    ├── Image/
    ├── CMakeLists.txt
    └── .gitignore
```

## 1. PPM Image Format

PPM (Portable Pixmap) is a simple text-based format starting with "P3" for color images, followed by width, height, max color value (255), and RGB pixel values. [davis.lbl](https://davis.lbl.gov/Manuals/NETPBM/doc/ppm.html)

The C++ output uses:
```cpp
std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
```
This generates a viewable gradient image. [realtimerendering](https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf)

## Render Script

`render.sh` is well-structured for Fedora: it cleans/builds with CMake, runs the executable, saves to `RayTracing/Image/output.ppm`, and converts to PNG using ImageMagick's `convert` if available. [cs.swarthmore](https://www.cs.swarthmore.edu/~soni/cs35/f13/Labs/extras/01/ppm_info.html)

Here's the code-block:

```bash
#!/bin/bash
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

if [ "$1" = "clean" ]; then
    echo -e "${YELLOW}=== Cleaning build directory ===${NC}"
    rm -rf build
    cmake -B build
fi

echo -e "${BLUE}=== Building Ray Tracer ===${NC}"
cmake --build build -j$(nproc)

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Build successful!${NC}"
    echo -e "${BLUE}=== Rendering image ===${NC}"
    mkdir -p RayTracing/Image
    START_TIME=$(date +%s)
    ./build/inOneWeekend > RayTracing/Image/output.ppm
    if [ $? -eq 0 ]; then
        END_TIME=$(date +%s)
        ELAPSED=$((END_TIME - START_TIME))
        echo -e "${GREEN}✓ Render complete in ${ELAPSED}s!${NC}"
        echo -e "${GREEN}  Image saved to RayTracing/Image/output.ppm${NC}"
        if command -v convert &> /dev/null; then
            convert RayTracing/Image/output.ppm RayTracing/Image/output.png
            echo -e "${GREEN}  PNG saved to RayTracing/Image/output.png${NC}"
        fi
    else
        echo -e "${RED}✗ Render failed!${NC}"
    fi
else
    echo -e "${RED}✗ Build failed!${NC}"
fi
```
## Output (Note: PNG is not obtained directly):
![First Ray Tracer Image](Image/output.png)

## 2. Vector 3 class
Instead of using vector 4, I will be using vector 3 since it's not wrong. 
```cpp
class vec3 {
  public:
    double v[3];
    vec3() : v{0,0,0} {
    }
    vec3(double v0, double v1, double v2) : v{v0, v1, v2} {
    }
    double x() const {
        return v[0];
    }
    double y() const {
        return v[1];
    }
    double z() const {
        return v[2];
    }
};
```
This vec 3 can be used for defining colors, position. Also, I am in no short of memory so I am using double instead of float.
Now, create color utility functions using the above class, i.e. vec3.
```cpp
void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
```

Call this function inside main() in main.cpp as such:
```cpp
auto pixel_color = color(double(i)/(imageWidth-1), double(j)/(imageHeight-1), 0);
            write_color(std::cout, pixel_color);
```

## Output (Note: We get the same output):
![First Ray Tracer Image](Image/output.png)
