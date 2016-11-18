// ==========================================================================
// Barebones OpenGL Core Profile Boilerplate
//    using the GLFW windowing system (http://www.glfw.org)
//
// Loosely based on
//  - Chris Wellons' example (https://github.com/skeeto/opengl-demo) and
//  - Camilla Berglund's example (http://www.glfw.org/docs/latest/quick.html)
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <glm/glm.hpp>
#include "ImageBuffer.h"
#include "SceneReader.h"
#include "Sphere.h"

// Specify that we want the OpenGL core profile before including GLFW headers
#ifdef _WIN32
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#else
#include <glad/glad.h>
#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

using namespace glm;
using namespace std;

// --------------------------------------------------------------------------
// OpenGL utility and support function prototypes

void QueryGLVersion();
bool CheckGLErrors();

// Global Variables
float fov_ = 55.0f;
int scene_ = 0;
I_Shape* DEFAULT_SHAPE = new Sphere(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

// --------------------------------------------------------------------------
// GLFW callback functions

// reports GLFW errors
void ErrorCallback(int error, const char* description)
{
   cout << "GLFW ERROR " << error << ":" << endl;
   cout << description << endl;
}

// handles keyboard input events
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
   else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
   {
      scene_ = (scene_ + 1) % 2;
   }
   else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
   {
      scene_ = (scene_ - 1);
      if (scene_ == -1)
         scene_ = 1;
   }
}

bool isShadow(SceneReader& reader, vec3 point, vec3 dir)
{
   float t;

    // see if any shapes intersect
    for each(I_Shape* shape in reader.shapes)
    { 
       vec3 intersection = shape->intersects(point, dir, t);
       if (intersection != vec3(-1.0f) && t > 0)
        {
           //return true;
        }
    }

    return false;
}

vec3 shading(I_Shape* shape, vec3 intersection, vec3 view, SceneReader& reader)
{
   vec3 colour = shape->colour() * 0.4f;
   vec3 light = normalize(reader.lights.at(0)->point - intersection);

   if (!isShadow(reader, intersection, light))
   {
       vec3 diffuse = shape->colour() * max(0, dot(shape->normal(), light));

       vec3 h = normalize(view + light);
       vec3 specular = vec3(0.3f * pow(max(0, dot(shape->normal(), h)), shape->phongExp()));

       colour += diffuse + specular;
   }

   return colour;
}

void rayGeneration(ImageBuffer& image, SceneReader& reader)
{
   vec3 rayOrigin = vec3(0.0f);
   vec3 rayDirection;

   // focal length
   float z = -1.0f * (1.0f / tan(fov_ / 2.0f));

   // intersecting shape
   float t = INFINITY;
   float minT = INFINITY;
   I_Shape* currShape = DEFAULT_SHAPE;
   vec3 currIntersection = vec3(-1.0f);

   // Loop over every pixel
   for (int y = 0; y < image.Height(); ++y){
      for (int x = 0; x < image.Width(); ++x){

         // map x and y to screen coordinates
         float screenX = (2.0f * ((x + 0.5f) / image.Width()) - 1.0f) * static_cast<float>(tan(0.5f * M_PI * fov_ / 180.0f));
         float screenY = (1.0f - 2.0f * ((y + 0.5f) / image.Height())) * static_cast<float>(tan(0.5f * M_PI * fov_ / 180.0f));

         // find point
         rayDirection = normalize(vec3(-1.0f * screenX, screenY, z));

         // see if any shapes intersect
         for each(I_Shape* shape in reader.shapes)
         {
            vec3 intersection = shape->intersects(rayOrigin, rayDirection, t);
            if (intersection != vec3(-1.0f))
            {
               if (abs(t) < minT)
               {
                  minT = abs(t);
                  currShape = shape;
                  currIntersection = intersection;
               }
            }
         }

         vec3 colour = shading(currShape, currIntersection, rayDirection, reader);

         // Set Pixel
         image.SetPixel(x, y, colour);

         // reset state
         minT = INFINITY;
         currShape = DEFAULT_SHAPE;
         currIntersection = vec3(-1.0f);
      }
   }
}

// ==========================================================================
// PROGRAM ENTRY POINT

int main(int argc, char *argv[])
{
   // initialize the GLFW windowing system
   if (!glfwInit()) {
      cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
      return -1;
   }
   glfwSetErrorCallback(ErrorCallback);

   // attempt to create a window with an OpenGL 4.1 core profile context
   GLFWwindow *window = 0;
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   window = glfwCreateWindow(512, 512, "CPSC 453 OpenGL Assignment 4", 0, 0);
   if (!window) {
      cout << "Program failed to create GLFW window, TERMINATING" << endl;
      glfwTerminate();
      return -1;
   }

   // set keyboard callback function and make our context current (active)
   glfwSetKeyCallback(window, KeyCallback);
   glfwMakeContextCurrent(window);

   //Intialize GLAD
   if (!gladLoadGL())
   {
      cout << "GLAD init failed" << endl;
      return -1;
   }

   // query and print out information about our OpenGL environment
   QueryGLVersion();

   // Image Buffer Stuff
   ImageBuffer image;
   image.Initialize();

   SceneReader reader;

   int currScene = -1;

   // run an event-triggered main loop
   while (!glfwWindowShouldClose(window))
   {
      if (currScene != scene_)
      {
         if (scene_ == 0)
         {
            reader.readScene("scenes/scene1.txt");
         }
         else
         {
            reader.readScene("scenes/scene2.txt");
         }

         rayGeneration(image, reader);

         image.Render(); // Render the image
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   // save image to file
   //image.SaveToFile("AwesomeRayTrace.png");

   // clean up allocated resources before exit
   image.Destroy();
   glfwDestroyWindow(window);
   glfwTerminate();

   cout << "Goodbye!" << endl;
   return 0;
}

// ==========================================================================
// SUPPORT FUNCTION DEFINITIONS

// --------------------------------------------------------------------------
// OpenGL utility functions

void QueryGLVersion()
{
   // query opengl version and renderer information
   string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
   string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
   string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

   cout << "OpenGL [ " << version << " ] "
      << "with GLSL [ " << glslver << " ] "
      << "on renderer [ " << renderer << " ]" << endl;
}

bool CheckGLErrors()
{
   bool error = false;
   for (GLenum flag = glGetError(); flag != GL_NO_ERROR; flag = glGetError())
   {
      cout << "OpenGL ERROR:  ";
      switch (flag) {
      case GL_INVALID_ENUM:
         cout << "GL_INVALID_ENUM" << endl; break;
      case GL_INVALID_VALUE:
         cout << "GL_INVALID_VALUE" << endl; break;
      case GL_INVALID_OPERATION:
         cout << "GL_INVALID_OPERATION" << endl; break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
         cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << endl; break;
      case GL_OUT_OF_MEMORY:
         cout << "GL_OUT_OF_MEMORY" << endl; break;
      default:
         cout << "[unknown error code]" << endl;
      }
      error = true;
   }
   return error;
}