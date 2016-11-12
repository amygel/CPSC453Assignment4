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
   // total area
   mat3 A;
   A[0] = vec3(p1.x - p2.x, p1.x - p3.x, dir.x);
   A[1] = vec3(p1.y - p2.y, p1.y - p3.y, dir.y);
   A[2] = vec3(p1.z - p2.z, p1.z - p3.z, dir.z);

   // matrix for u value
   mat3 matrix;
   matrix[0] = vec3(p1.x - origin.x, p1.x - p3.x, dir.x);
   matrix[1] = vec3(p1.y - origin.y, p1.y - p3.y, dir.y);
   matrix[2] = vec3(p1.z - origin.z, p1.z - p3.z, dir.z);

   float u = determinant(matrix) / determinant(A);

   // matrix for v value
   matrix[0] = vec3(p1.x - p2.x, p1.x - origin.x, dir.x);
   matrix[1] = vec3(p1.y - p2.y, p1.y - origin.y, dir.y);
   matrix[2] = vec3(p1.z - p2.z, p1.z - origin.z, dir.z);

   float v = determinant(matrix) / determinant(A);

   // check intersection
   if (u > 0 && v > 0 && 1-u-v > 0)
   {
      return true;
   }

   return false;
}

vec3 Triangle::colour()
{
   return colour_;
}