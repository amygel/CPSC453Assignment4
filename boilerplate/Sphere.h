#include <glm/glm.hpp>
#include "I_Shape.h"

using namespace glm;

class Sphere : public I_Shape
{
public:
   Sphere(float x, float y, float z, float radius,
      float r, float g, float b,
      float phongExp,
      bool isRelfective);
   ~Sphere();

   virtual vec3 intersects(vec3 origin, vec3 dir, float& t);
   virtual vec3 colour();
   virtual vec3 normal();
   virtual float phongExp();
   virtual bool isRelfective();

private:
   vec3 colour_;
   vec3 center_;
   vec3 normal_;
   float radius_;
   vec3 intersectionPoint_;
   float phongExp_;
   bool isRelfective_;
};