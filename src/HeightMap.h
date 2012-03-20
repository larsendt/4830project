#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <GL/gl.h>

#include "VertexBufferObject.h"
#include "OCLNoise.h"
#include "OCLKernel.h"

class HeightMap
{
	public:
		HeightMap();
		~HeightMap();
		void nextHeightMap();
		void draw();
		
	private:
		OCLNoise* m_noise;
		OCLKernel* m_kernel;
		VertexBufferObject* m_vbo;
		int m_currentNoiseIndex;
		
		int m_dim;
		unsigned char* m_noiseMap;
		float* m_vertices;
		float* m_normals;
		Vertex* m_interleaved;
		unsigned int* m_indices;
		int m_numVertices;
		int m_numIndices;
		float m_spacing;
		
};

#endif
