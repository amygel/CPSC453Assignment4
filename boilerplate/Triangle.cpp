#include "Triangle.h"

Triangle::Triangle(float p1x, float p1y, float p1z,
   float p2x, float p2y, float p2z,
   float p3x, float p3y, float p3z,
   float r, float g, float b)
   : p1(p1x, p1y, p1z)
   , p2(p2x, p2y, p2z)
   , p3(p3x, p3y, p3z)
   , colour_(r, g, b)
{
}

Triangle::~Triangle()
{
}

bool Triangle::intersects(vec3 origin, vec3 dir)
{
   return false;
}

vec3 Triangle::colour()
{
   return colour_;
}