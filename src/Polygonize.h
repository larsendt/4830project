/////////////
//Polygonize.h
/////////////


#ifndef POLYGONIZE
#define POLYGONIZE


#include "MeshObject.h"
#include "Types.h"
#include "VoxelCube.h"
#include <math.h>

MeshObject * convertToMesh(MeshObject * mesh, VoxelCube voxels, int dim, float spacing = 1.0, unsigned char isolevel = 128);

COORD3D vInterpolation(unsigned int isolevel,
								 COORD3D p1,
								 COORD3D p2,
								 unsigned char v1,
								 unsigned char v2);
								 
#endif
