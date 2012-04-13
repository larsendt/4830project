#ifndef OCL_MARCHING_CUBES_H
#define OCL_MARCHING_CUBES_H

#include <GL/gl.h>

#include "OCLKernel.h"
#include "Types.h"

class OCLMarchingCubes
{
	public:
		OCLMarchingCubes();
		
		void generateMesh(unsigned char* noise, int dim, float spacing);
		
		VERTEX* vertices() { return m_vertices; }
		int vertexCount() { return m_vertexCount; }
		GLuint* indices() { return m_indices; }
		int indexCount() { return m_indexCount; }
		
	private:
		void analyze();
		void generate();
	
		OCLKernel* m_kernel;
		VERTEX* m_vertices;
		GLuint* m_indices;
		int m_vertexCount;
		int m_indexCount;
		int m_dim;
		float m_spacing;
		unsigned char* m_noise;
};

#endif
