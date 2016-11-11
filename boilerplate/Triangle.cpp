#include "Triangle.h"

Triangle::Triangle(float p1x, float p1y, float p1z,
   float p2x, float p2y, float p2z,
   float p3x, float p3y, float p3z)
   : p1x(p1x), p1y(p1y), p1z(p1z)
   , p2x(p2x), p2y(p2y), p2z(p2z)
   , p3x(p3x), p3y(p3y), p3z(p3z)
{
}

Triangle::~Triangle()
{
}