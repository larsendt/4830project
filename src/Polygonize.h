/////////////
//Polygonize.h
/////////////


#ifndef POLYGONIZE
#define POLYGONIZE


#include "MeshObject.h"
#include "Types.h"
#include <math.h>

MeshObject * convertToMesh(MeshObject * mesh, unsigned char * voxels, int xsize, int ysize, int zsize, float spacing = 1.0, unsigned char isolevel = 128);
int index1D(int x, int y, int z, int xsize, int ysize, int zsize);
COORD3D vInterpolation(unsigned int isolevel,
								 COORD3D p1,
								 COORD3D p2,
								 unsigned char v1,
								 unsigned char v2);
								 
#endif
