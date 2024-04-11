# RayTracingInOneWeekend
A project following a wonderful ray tracing tutorial book called [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

### Major differences with the book
- [_glm_](https://github.com/HappyFaceFriend/glm) is used for vector and color representations.
- [_lodepng_](https://github.com/lvandeve/lodepng) is used to output the image as a PNG file, instead of a PPM file.
- File structure and conventions are differnt from the original book. I tried to write the code in a more 'C++ way'.


## How to build
This project only supports Windows x64, but you will probably be able to use the same source files and run it in different platfoms.

### Windows

1. Clone this repository and all of its submodules
```
$ git clone --recursive https://github.com/HappyFaceFriend/RayTracingInOneWeekend
```
2. Run `GenerateProject.bat` to generate a vs2022 project.

    - If you are not using vs2022, modify the bat file to your desired IDE

3. Build the project in visual studio

4. The resulting image will be under the directory `RayTracingInOneWeekend`.
