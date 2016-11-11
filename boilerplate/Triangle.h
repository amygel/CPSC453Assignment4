#include <glm/glm.hpp>
#include "I_Shape.h"

using namespace glm;

class Triangle : public I_Shape
{
public:
   Triangle(float p1x, float p1y, float p1z,
      float p2x, float p2y, float p2z,
      float p3x, float p3y, float p3z,
      float r, float g, float b);
   ~Triangle();

   virtual bool intersects(vec3 origin, vec3 dir);
   virtual vec3 colour();

   vec3 p1;
   vec3 p2;
   vec3 p3;

private:
   vec3 colour_;
};