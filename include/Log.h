#pragma once

#include <iostream>

#include "Maths.h"
#include "Phong.h"
#include "PhongReflective.h"
#include "Texture.h"

std::ostream &operator<<(std::ostream &os, const Vec3 &v);

std::ostream &operator<<(std::ostream &os, const PhongConfig &config);
std::ostream &operator<<(std::ostream &os, const PhongReflectiveConfig &config);

std::ostream &operator<<(std::ostream &os, TextureFilter type);
std::ostream &operator<<(std::ostream &os, TextureWrap type);
std::ostream &operator<<(std::ostream &os, TextureSampleParams params);
