#include <glm/glm.hpp>

using namespace glm;

class Light
{
public:
   Light(float x, float y, float z);
   ~Light();

   vec3 point;
};