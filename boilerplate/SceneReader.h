#include <string>
#include <vector>
#include "Light.h"
#include "I_Shape.h"

class SceneReader
{
public:
   SceneReader();
   ~SceneReader();

   void readScene(std::string fileName);

   std::vector<Light*> lights;
   std::vector<I_Shape*> shapes;

private:
   void clearVectors();
};