#ifndef SOFTWARE_MARCHING_CUBES_H
#define SOFTWARE_MARCHING_CUBES_H


#include "Types.h"
#include "VertexBufferObject.h"

class SoftwareMarchingCubes
{
	public:
		SoftwareMarchingCubes();
		~SoftwareMarchingCubes();
		void setVoxelData(VOXEL* voxels, int count);
		void draw();
	
	private:
		VertexBufferObject* m_vbo;
		int m_voxelCount;
};

#endif
