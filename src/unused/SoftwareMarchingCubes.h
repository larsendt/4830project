#ifndef SOFTWARE_MARCHING_CUBES_H
#define SOFTWARE_MARCHING_CUBES_H

#include "Types.h"
#include "VertexBufferObject.h"
#include "MeshObject.h"
#include "Vec3.h"
#include <math.h>


/*class SoftwareMarchingCubes
{
	public:
		SoftwareMarchingCubes();
		~SoftwareMarchingCubes();
		void setNoiseData(unsigned char* noise, int dim, float spacing);
		void runOutToMesh(MeshObject * mesh);
		void draw();
	
	private:
		int index1D(int x, int y, int z);
		
		int m_dim;
		
		unsigned char * m_noise;
		
		float m_spacing;
		
		COORD3D vInterpolation(unsigned int isolevel,
								 COORD3D p1,
								 COORD3D p2,
								 unsigned char v1,
								 unsigned char v2); 
								 
		COORD3D getEdgeVertex(int edgenum);
		
};*/

#endif
