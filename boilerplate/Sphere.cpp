#include "Sphere.h"
#include <math.h>

Sphere::Sphere(float x, float y, float z, float radius,
   float r, float g, float b,
   float phongExp,
   bool isRelfective)
   : center_(x, y, z)
   , radius_(radius)
   , normal_(vec3(0.0f))
   , colour_(r, g, b)
   , intersectionPoint_(-1.0f, -1.0f, -1.0f)
   , phongExp_(phongExp)
   , isRelfective_(isRelfective)
{
}

Sphere::~Sphere()
{
}

vec3 Sphere::intersects(vec3 origin, vec3 dir, float& t)
{
   float a = dot(dir, dir);
   float b = dot(dir, origin - center_);
   float c = dot(origin - center_, origin - center_) - (radius_*radius_);

   if ((b*b) - a*c < 0)
   {
      return vec3(-1.0f);
   }

   // find intersection point
   float t1 = (-1.0f * b + sqrt((b*b) - (a*c))) / a;
   float t2 = (-1.0f * b - sqrt((b*b) - (a*c))) / a;

   if (t1 > t2)
   {
      t = t1;
   }
   else
   {
      t = t2;
   }

   intersectionPoint_ = origin + t * dir;

   // If calculating light ray, update normal
   if (origin == vec3(0.0f))
   {
       normal_ = normalize(intersectionPoint_ - center_);
   }
   
   return intersectionPoint_;
}

vec3 Sphere::colour()
{
   return colour_;
}

vec3 Sphere::normal()
{
   return normal_;
}

float Sphere::phongExp()
{
   return phongExp_;
}

bool Sphere::isRelfective()
{
   return isRelfective_;
}