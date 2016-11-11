#include "Plane.h"

Plane::Plane(float nx, float ny, float nz,
   float px, float py, float pz,
   float r, float g, float b)
   : normal(nx, ny, nz)
   , point(px, py, pz)
   , colour_(r, g, b)
{
}

Plane::~Plane()
{
}

bool Plane::intersects(vec3 origin, vec3 dir)
{
   return false;
}

vec3 Plane::colour()
{
   return colour_;
}