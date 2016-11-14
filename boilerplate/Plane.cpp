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

bool Plane::intersects(vec3 origin, vec3 dir, float& t)
{
   t = dot(point_, normal_) / dot(dir, normal_);
   vec3 p = t*dir;

   if (dot(p - point_, normal_) == 0)
   {
      return true;
   }

   return false;
}

vec3 Plane::colour()
{
   return colour_;
}

vec3 Plane::normal()
{
   return normal_;
}

float Plane::phongExp()
{
   return phongExp_;
}