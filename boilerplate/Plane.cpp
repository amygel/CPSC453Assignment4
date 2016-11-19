#include "Plane.h"
#include "iostream"

using namespace std; 

Plane::Plane(float nx, float ny, float nz,
   float px, float py, float pz,
   float r, float g, float b,
   float phongExp,
   bool isRelfective)
   : normal_(nx, ny, nz)
   , point_(px, py, pz)
   , colour_(r, g, b)
   , phongExp_(phongExp)
   , isRelfective_(isRelfective)
{
   normal_ = -1.0f * normalize(normal_);
}

Plane::~Plane()
{
}

vec3 Plane::intersects(vec3 origin, vec3 dir, float& t)
{
   float denom = dot(normal_, dir);
   //cout << "denom " << denom << endl;

   if (denom > 0.0f)
   {
      t = dot(point_ - origin, normal_) / denom;
      //cout << t << endl;

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

bool Plane::isRelfective()
{
   return isRelfective_;
}