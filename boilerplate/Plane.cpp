#include "Plane.h"

Plane::Plane(float nx, float ny, float nz,
   float px, float py, float pz)
   : nx(nx), ny(ny), nz(nz)
   , px(px), py(py), pz(pz)
{
}

Plane::~Plane()
{
}