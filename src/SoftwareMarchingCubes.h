#ifndef SOFTWARE_MARCHING_CUBES_H
#define SOFTWARE_MARCHING_CUBES_H

#include "Types.h"
#include "VertexBufferObject.h"

class SoftwareMarchingCubes
{
	public:
		SoftwareMarchingCubes();
		~SoftwareMarchingCubes();
		void setNoiseData(unsigned char* noise, int dim, float spacing);
		void draw();
	
	private:
		int index1D(int x, int y, int z);
		
		VertexBufferObject* m_vbo;
		int m_dim;
};

#endif
