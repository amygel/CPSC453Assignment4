#include <string>
#include <vector>

class Light;
class Sphere;
class Plane;
class Triangle;

class SceneReader
{
public:
   SceneReader();
   ~SceneReader();

   void readScene(std::string fileName);

   std::vector<Light> lights;
   std::vector<Sphere> spheres;
   std::vector<Plane> planes;
   std::vector<Triangle> triangles;

private:
   void clearVectors();
};