#ifndef VOXEL_GEN_H
#define VOXEL_GEN_H

#include "Types.h"

class VoxelGen
{
	public:
		VoxelGen();
		~VoxelGen();
		void set3DNoiseData(unsigned char* data, int dim, float spacing);
		VOXEL* voxelData() { return m_voxels; }
		int voxelCount() { return m_voxelCount; }
		
	private:
		VOXEL* m_voxels;
		int m_voxelCount;
};

#endif
