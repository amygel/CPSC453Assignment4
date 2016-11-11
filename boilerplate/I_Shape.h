#pragma once

#include <glm/glm.hpp>

using namespace glm;

class I_Shape
{
public:
   I_Shape(){}
   ~I_Shape(){}

   virtual bool intersects(vec3 origin, vec3 dir) = 0;
   virtual vec3 colour() = 0;
};