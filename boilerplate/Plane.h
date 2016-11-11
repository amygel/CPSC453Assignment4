#include <glm/glm.hpp>
#include "I_Shape.h"

using namespace glm;

class Plane : public I_Shape
{
public:
   Plane(float nx, float ny, float nz,
      float px, float py, float pz,
      float r, float g, float b);
   ~Plane();

   virtual bool intersects(vec3 origin, vec3 dir);
   virtual vec3 colour();

   vec3 normal;
   vec3 point;

private:
   vec3 colour_;
};