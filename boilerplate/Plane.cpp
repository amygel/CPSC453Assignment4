#include "Plane.h"

Plane::Plane(float nx, float ny, float nz,
   float px, float py, float pz,
   float r, float g, float b,
   float phongExp)
   : normal_(nx, ny, nz)
   , point_(px, py, pz)
   , colour_(r, g, b)
   , phongExp_(phongExp)
{
   normal_ = normalize(normal_);
}

Plane::~Plane()
{
}

vec3 Plane::intersects(vec3 origin, vec3 dir, float& t)
{
   float denom = dot(normal_, dir);

   if (denom > 0.0f)
   {
      t = (-1.0 * dot(point_ - origin, normal_)) / denom;

      if (t > 0.0f)
      {
         return origin + t*dir;
      }
   }

   return vec3(-1.0f);
}

vec3 Plane::colour()
{
   return colour_;
}

vec3 Plane::normal()
{
   return -1.0f * normal_;
}

float Plane::phongExp()
{
   return phongExp_;
}