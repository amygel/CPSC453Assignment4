#include <glm/glm.hpp>
#include "I_Shape.h"

using namespace glm;

class Plane : public I_Shape
{
public:
   Plane(float nx, float ny, float nz,
      float px, float py, float pz,
      float r, float g, float b,
      float phongExp);
   ~Plane();

   virtual vec3 intersects(vec3 origin, vec3 dir, float& t);
   virtual vec3 colour();
   virtual vec3 normal();
   virtual float phongExp();

private:
   vec3 point_;
   vec3 normal_;
   vec3 colour_;
   float phongExp_;
};