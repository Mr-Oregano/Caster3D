# Caster3D
CPU raytracer written in C++.

# Demo
![out](https://user-images.githubusercontent.com/33503562/157174759-373488cb-b3ed-4b1b-acd9-4724342e7ad7.png)

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
