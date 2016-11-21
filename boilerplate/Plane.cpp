#include "Plane.h"
#include "iostream"

using namespace std; 

Plane::Plane(float nx, float ny, float nz,
   float px, float py, float pz,
   float r, float g, float b,
   float phongExp,
   float reflectivity)
   : normal_(nx, ny, nz)
   , point_(px, py, pz)
   , colour_(r, g, b)
   , phongExp_(phongExp)
   , reflectivity_(reflectivity)
{
   normal_ = -1.0f * normalize(normal_);
}

Plane::~Plane()
{
}

vec3 Plane::intersects(vec3 origin, vec3 dir, float& t)
{
   float denom = dot(normal_, dir);

   if (denom > 0.0f)
   {
      t = dot(point_ - origin, normal_) / denom;

      if (t > 0.0f)
      {
         return origin + t*dir;
      }
   }

   return vec3(-999.0f);
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

float Plane::reflectivity()
{
   return reflectivity_;
}