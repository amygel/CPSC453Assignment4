#include "Triangle.h"

Triangle::Triangle(float p1x, float p1y, float p1z,
   float p2x, float p2y, float p2z,
   float p3x, float p3y, float p3z,
   float r, float g, float b,
   float phongExp,
   float reflectivity)
   : p1_(p1x, p1y, p1z)
   , p2_(p2x, p2y, p2z)
   , p3_(p3x, p3y, p3z)
   , colour_(r, g, b)
   , phongExp_(phongExp)
   , reflectivity_(reflectivity)
{
   normal_ = normalize(cross(p2_ - p1_, p3_ - p1_));
}

Triangle::~Triangle()
{
}

vec3 Triangle::intersects(vec3 origin, vec3 dir, float& t)
{
   // total area
   mat3 A;
   A[0] = vec3(p1_.x - p2_.x, p1_.x - p3_.x, dir.x);
   A[1] = vec3(p1_.y - p2_.y, p1_.y - p3_.y, dir.y);
   A[2] = vec3(p1_.z - p2_.z, p1_.z - p3_.z, dir.z);

   // matrix for u value
   mat3 matrix;
   matrix[0] = vec3(p1_.x - origin.x, p1_.x - p3_.x, dir.x);
   matrix[1] = vec3(p1_.y - origin.y, p1_.y - p3_.y, dir.y);
   matrix[2] = vec3(p1_.z - origin.z, p1_.z - p3_.z, dir.z);

   float u = determinant(matrix) / determinant(A);

   // matrix for v value
   matrix[0] = vec3(p1_.x - p2_.x, p1_.x - origin.x, dir.x);
   matrix[1] = vec3(p1_.y - p2_.y, p1_.y - origin.y, dir.y);
   matrix[2] = vec3(p1_.z - p2_.z, p1_.z - origin.z, dir.z);

   float v = determinant(matrix) / determinant(A);

   // check intersection
   if (u > 0 && v > 0 && 1 - u - v > 0)
   {
      // matrix for t value
      matrix[0] = vec3(p1_.x - p2_.x, p1_.x - p3_.x, p1_.x - origin.x);
      matrix[1] = vec3(p1_.y - p2_.y, p1_.y - p3_.y, p1_.y - origin.y);
      matrix[2] = vec3(p1_.z - p2_.z, p1_.z - p3_.z, p1_.z - origin.z);

      t = determinant(matrix) / determinant(A);

      if (t > 0.0f)
      {
         return origin + t*dir;
      }   
   }

   return vec3(-1.0f);
}

vec3 Triangle::colour()
{
   return colour_;
}

vec3 Triangle::normal()
{
   return normal_;
}

float Triangle::phongExp()
{
   return phongExp_;
}

float Triangle::reflectivity()
{
   return reflectivity_;
}