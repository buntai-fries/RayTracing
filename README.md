# RayTracing

-> This project structure is as such:
RayTracingMain/
├── render.sh
└── RayTracing/
    ├── src/
    ├── Image/
    ├── CMakeLists.txt
    └── .gitignore

1) Rendering the first image in PPM format:

-> Given below is the PPM image format:
<img width="800" height="244" alt="image" src="https://github.com/user-attachments/assets/9d1ba5d6-3f7c-40a6-a6c0-c1aad55f9329" />
                                                  Source: Wikipedia

The code given below helps us to specify the format of the image, i.e. PPM.
// std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

After, we are done with the code. We convert it into image file. Since we are using C++, CMake is the best choice for that. I am in "fedora-linux" so to avoid the long CLI-interaction, I run "./render.sh" after I build the CMake to make things easier.

#File ---> render.sh:

"""
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
    mkdir -p RayTracing
    START_TIME=$(date +%s)
    ./build/inOneWeekend > RayTracing/Image/output.ppm
    if [ $? -eq 0 ]; then
        END_TIME=$(date +%s)
        ELAPSED=$((END_TIME - START_TIME))
        echo -e "${GREEN}✓ Render complete in ${ELAPSED}s!${NC}"
        echo -e "${GREEN}  Image saved to RayTracing/output.ppm${NC}"
        if command -v convert &> /dev/null; then
            convert RayTracing/Image/output.ppm RayTracing/output.png
            echo -e "${GREEN}  PNG saved to RayTracing/output.png${NC}"
        fi
    else
        echo -e "${RED}✗ Render failed!${NC}"
    fi
else
    echo -e "${RED}✗ Build failed!${NC}"
fi
"""

Then, we get our first PPM-Format Image.
<img width="256" height="256" alt="image" src="https://github.com/user-attachments/assets/137b446e-e61d-42dc-b423-118becfb5247" />
Note: The script manages the image location so it will automatically add it inside the Image folder.

