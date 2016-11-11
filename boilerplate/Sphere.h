#include <glm/glm.hpp>
#include "I_Shape.h"

using namespace glm;

class Sphere : public I_Shape
{
public:
   Sphere(float x, float y, float z, float radius,
      float r, float g, float b);
   ~Sphere();

   virtual bool intersects(vec3 origin, vec3 dir);
   virtual vec3 colour();

   vec3 center;
   float radius;

private:
   vec3 colour_;
};