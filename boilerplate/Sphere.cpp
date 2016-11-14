#include "Sphere.h"
#include <math.h>

Sphere::Sphere(float x, float y, float z, float radius,
   float r, float g, float b,
   float phongExp)
   : center_(x, y, z)
   , radius_(radius)
   , colour_(r, g, b)
   , intersectionPoint_(-1.0f, -1.0f, -1.0f)
   , phongExp_(phongExp)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersects(vec3 origin, vec3 dir, float& t)
{
   float a = dot(dir, dir);
   float b = dot(dir, origin - center_);
   float c = dot(origin - center_, origin - center_) - (radius_*radius_);

   if ((b*b) - a*c < 0)
   {
      return false;
   }

   // find intersection point
   float t1 = (-1.0f * b + sqrt((b*b) - (a*c))) / a;
   float t2 = (-1.0f * b - sqrt((b*b) - (a*c))) / a;

   if (t1 < t2)
   {
      t = t1;
   }
   else
   {
      t = t2;
   }
   intersectionPoint_ = t * dir;

   return true;
}

vec3 Sphere::colour()
{
   return colour_;
}

vec3 Sphere::normal()
{
  return normalize(intersectionPoint_ - center_);
}

float Sphere::phongExp()
{
   return phongExp_;
}