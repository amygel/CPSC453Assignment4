#include "SceneReader.h"

#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

SceneReader::SceneReader()
{
}

SceneReader::~SceneReader()
{
}

void SceneReader::readScene(std::string fileName)
{
   clearVectors();

   // open file for reading
   std::ifstream infile(fileName);

   // read file line by line
   std::string line;
   while (std::getline(infile, line))
   {
      // Ignore comments, closing brackets, and blank lines
      if (line == "" || line.at(0) == '#' || line.at(0) == '}')
      {
         continue;
      }

      if (line.find("light") != std::string::npos)
      {
         // read point
         std::getline(infile, line);

         std::istringstream iss(line);
         float x, y, z;
         if (!(iss >> x >> y >> z)) { break; } // error

         // create light
         Light* l = new Light(x, y, z);
         lights.push_back(l);
      }
      else if (line.find("sphere") != std::string::npos)
      {
         // read center point
         std::getline(infile, line);

         std::istringstream iss1(line);
         float x, y, z;
         if (!(iss1 >> x >> y >> z)) { break; } // error

         // read radius
         std::getline(infile, line);

         std::istringstream iss2(line);
         float radius;
         if (!(iss2 >> radius)) { break; } // error

         // read colour
         std::getline(infile, line);

         std::istringstream iss3(line);
         float r, g, b;
         if (!(iss3 >> r >> g >> b)) { break; } // error

         // read phong exponent
         std::getline(infile, line);

         std::istringstream iss4(line);
         float p;
         if (!(iss4 >> p)) { break; } // error

         // read if is reflective
         std::getline(infile, line);

         std::istringstream iss5(line);
         float reflectivity;
         if (!(iss5 >> reflectivity)) { break; } // error

         // creat sphere
         Sphere* s = new Sphere(x, y, z, radius, r, g, b, p, reflectivity);
         shapes.push_back(s);
      }
      else if (line.find("plane") != std::string::npos)
      {
         // read normal
         std::getline(infile, line);

         std::istringstream iss1(line);
         float nx, ny, nz;
         if (!(iss1 >> nx >> ny >> nz)) { break; } // error

         // read point
         std::getline(infile, line);

         std::istringstream iss2(line);
         float px, py, pz;
         if (!(iss2 >> px >> py >> pz)) { break; } // error

         // read colour
         std::getline(infile, line);

         std::istringstream iss3(line);
         float r, g, b;
         if (!(iss3 >> r >> g >> b)) { break; } // error

         // read phong exponent
         std::getline(infile, line);

         std::istringstream iss4(line);
         float p;
         if (!(iss4 >> p)) { break; } // error

         // read if is reflective
         std::getline(infile, line);

         std::istringstream iss5(line);
         float reflectivity;
         if (!(iss5 >> reflectivity)) { break; } // error

         // create plane
         Plane* pl = new Plane(nx, ny, nz, px, py, pz, r, g, b, p, reflectivity);
         shapes.push_back(pl);
      }
      else if (line.find("triangle") != std::string::npos)
      {
         // read p1
         std::getline(infile, line);

         std::istringstream iss1(line);
         float p1x, p1y, p1z;
         if (!(iss1 >> p1x >> p1y >> p1z)) { break; } // error

         // read p2
         std::getline(infile, line);

         std::istringstream iss2(line);
         float p2x, p2y, p2z;
         if (!(iss2 >> p2x >> p2y >> p2z)) { break; } // error

         // read p3
         std::getline(infile, line);

         std::istringstream iss3(line);
         float p3x, p3y, p3z;
         if (!(iss3 >> p3x >> p3y >> p3z)) { break; } // error

         // read colour
         std::getline(infile, line);

         std::istringstream iss4(line);
         float r, g, b;
         if (!(iss4 >> r >> g >> b)) { break; } // error

         // read phong exponent
         std::getline(infile, line);

         std::istringstream iss5(line);
         float p;
         if (!(iss5 >> p)) { break; } // error

         // read if is reflective
         std::getline(infile, line);

         std::istringstream iss6(line);
         float reflectivity;
         if (!(iss6 >> reflectivity)) { break; } // error

         // create triangle
         Triangle* t = new Triangle(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z, r, g, b, p, reflectivity);
         shapes.push_back(t);
      }
   }
}

void SceneReader::clearVectors()
{
   lights.clear();
   shapes.clear();
}