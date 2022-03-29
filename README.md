# Caster3D
CPU raytracer written in C++.

# Demo
![out](https://user-images.githubusercontent.com/33503562/160544459-1da3871e-c0da-47de-8e16-7cb33f64f5ac.png)

# Build
Use [premake5](https://premake.github.io/) to create project files. Building should be relatively simple from there. Just build in your IDE of choice or `make.` if you're using make. 

(e.g. Run `premake5 vs2019` to create solution files for Visual Studio 2019)

# Dependencies

 - [stb](https://github.com/nothings/stb) (stb_image)
 - [glm](https://github.com/g-truc/glm)

 # Sources

  - https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates
  - https://en.wikipedia.org/wiki/Ray_tracing_(graphics)
  - https://math.hws.edu/graphicsbook/c8/s1.html
