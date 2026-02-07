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

Here's the cleaned, GitHub-ready bash block (fixed escapes and spacing):

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
#Output:
![First Ray Tracer Output](<img width="256" height="256" alt="image" src="https://github.com/user-attachments/assets/34d9d3ab-f569-44ad-99a1-dc1d5759d78e" />)
