#include "SceneReader.h"

#include "Light.h"
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
         Light l(x, y, z);
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

         // creat sphere
         Sphere s(x, y, z, radius);
         spheres.push_back(s);
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

         // create plane
         Plane p(nx, ny, nz, px, py, pz);
         planes.push_back(p);
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

         // create triangle
         Triangle t(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z);
         triangles.push_back(t);
      }
   }
}

void SceneReader::clearVectors()
{
   lights.clear();
   spheres.clear();
   planes.clear();
   triangles.clear();
}