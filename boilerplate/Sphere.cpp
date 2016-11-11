#include "Sphere.h"
#include <math.h>

Sphere::Sphere(float x, float y, float z, float radius,
   float r, float g, float b)
   : center(x, y, z)
   , radius(radius)
   , colour_(r, g, b)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersects(vec3 origin, vec3 dir)
{
   float a = dot(dir, dir);
   float b = dot(dir, origin - center);
   float c = dot(origin - center, origin - center) - (radius*radius);

   if ((b*b) - a*c < 0)
   {
      return false;
   }

   return true;
}

vec3 Sphere::colour()
{
   return colour_;
}