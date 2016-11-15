#include <glm/glm.hpp>
#include "I_Shape.h"

using namespace glm;

class Triangle : public I_Shape
{
public:
   Triangle(float p1x, float p1y, float p1z,
      float p2x, float p2y, float p2z,
      float p3x, float p3y, float p3z,
      float r, float g, float b,
      float phongExp);
   ~Triangle();

   virtual vec3 intersects(vec3 origin, vec3 dir, float& t);
   virtual vec3 colour();
   virtual vec3 normal();
   virtual float phongExp();

private:
   vec3 p1_;
   vec3 p2_;
   vec3 p3_;
   vec3 colour_;
   vec3 normal_;
   float phongExp_;
};