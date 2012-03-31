#ifndef SIMPLE_VOXEL_RENDERER_H
#define SIMPLE_VOXEL_RENDERER_H

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#include "Types.h"
#include "VertexBufferObject.h"

// renders voxels as a point cloud

class SimpleVoxelRenderer
{
	public:
		SimpleVoxelRenderer();
		~SimpleVoxelRenderer();
		void setVoxelData(VOXEL* voxels, int count);
		void draw();

	private:
		VertexBufferObject* m_vbo;
		int m_voxelCount;
};

#endif
