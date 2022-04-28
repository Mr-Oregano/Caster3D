# Caster3D
CPU raytracer written in C++.

# Demo
![out](https://user-images.githubusercontent.com/33503562/165689009-37a027e5-9a75-4163-a918-f9bfd9b656f5.png)
*Render time: `82.962` seconds*


# Build
Use [premake5](https://premake.github.io/) to create project files. Building should be relatively simple from there. Just build in your IDE of choice or `make.` if you're using make. 

(e.g. Run `premake5 vs2019` to create solution files for Visual Studio 2019)

# Dependencies

 - [stb](https://github.com/nothings/stb) (stb_image)
 - [glm](https://github.com/g-truc/glm)
 - [tiny_obj_loader](https://github.com/tinyobjloader/tinyobjloader)

 # Sources

  - https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates
  - https://en.wikipedia.org/wiki/Ray_tracing_(graphics)
  - https://math.hws.edu/graphicsbook/c8/s1.html
  - https://raytracing.github.io/books/RayTracingInOneWeekend.html
  - https://en.wikipedia.org/wiki/Path_tracing
  - https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
  - https://computergraphics.stackexchange.com/questions/4248/how-is-anti-aliasing-implemented-in-ray-tracing
