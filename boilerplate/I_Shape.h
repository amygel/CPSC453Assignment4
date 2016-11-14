#pragma once

#include <glm/glm.hpp>

using namespace glm;

class I_Shape
{
public:
   I_Shape(){}
   ~I_Shape(){}

   virtual bool intersects(vec3 origin, vec3 dir, float& t) = 0;
   virtual vec3 colour() = 0;
   virtual vec3 normal() = 0;
   virtual float phongExp() = 0;
};