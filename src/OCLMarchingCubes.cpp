#include "OCLMarchingCubes.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

OCLMarchingCubes::OCLMarchingCubes()
{
	m_vertices = NULL;
	m_indices = NULL;
	m_vertexCount = 0;
	m_indexCount = 0;
	m_kernel = new OCLKernel("kernels/marching_cubes.cl", "generateMesh");
}

void OCLMarchingCubes::generateMesh(unsigned char* noise, int dim, float spacing)
{
	m_dim = dim;
	m_noise = noise;
	m_spacing = spacing;
	
	// allocate the max, since I can't figure out how to
	// close pack the vertices in the kernel
	VERTEX* tmp_vertices = new VERTEX[dim*dim*dim*12];
	GLuint* tmp_indices = new GLuint[dim*dim*dim*12];
	
	if(m_vertices)
	{
		free(m_vertices);
		m_vertices = NULL;
	}
	
	if(m_indices)
	{
		free(m_indices);
		m_indices = NULL;
	}
	
	OCLArgument args[4];
	OCLArgument buffers[3];
	
	OCLArgument a;
	a.data = m_noise;
	a.byte_size = dim * dim * dim * sizeof(*noise);
	a.is_buffer = true;
	a.buffer_type = WRITE;
	a.buffer_index = 0;
	args[0] = a;
	buffers[0] = a;
	
	a.data = tmp_vertices;
	a.byte_size = dim * dim * dim * 12 * sizeof(*tmp_vertices);
	a.is_buffer = true;
	a.buffer_type = READ_WRITE;
	a.buffer_index = 1;
	args[1] = a;
	buffers[1] = a;
	
	a.data = tmp_indices;
	a.byte_size = dim * dim * dim * 12 * sizeof(*tmp_indices);
	a.is_buffer = true;
	a.buffer_type = READ_WRITE;
	a.buffer_index = 2;
	args[2] = a;
	buffers[2] = a;
	
	int tmp_dim = m_dim-1;
	a.data = &tmp_dim;
	a.byte_size = sizeof(tmp_dim);
	a.is_buffer = false;
	args[3] = a;
	
	if(!m_kernel->run(4, args, 3, buffers, m_dim*m_dim*m_dim, 1))
	{
		fprintf(stderr, "Error: mesh generation borked!\n");
		exit(1);
	}
	
	int max_vx = 32;
	m_vertexCount = 0;
	m_vertices = (VERTEX*) malloc(max_vx * sizeof(*m_vertices));
	m_indices = (GLuint*) malloc(max_vx * sizeof(*m_indices));
	for(int i = 0; i < dim*dim*dim*12; i++)
	{
		// if vertex was valid
		if(tmp_indices[i] & 0x40000000)
		{
			if(m_vertexCount >= max_vx)
			{ 
				max_vx *= 2;
				m_vertices = (VERTEX*) realloc(m_vertices, max_vx * sizeof(*m_vertices));
				m_indices = (GLuint*) realloc(m_indices, max_vx * sizeof(*m_indices));
				
				if(m_vertices == NULL || m_indices == NULL)
				{
					fprintf(stderr, "Failed to allocate memory for arrays.\n");
					exit(1);
				}
			}
		
			m_vertices[m_vertexCount] = tmp_vertices[i];
			m_indices[m_vertexCount] = tmp_indices[i] & 0x3fffffff;
			m_vertexCount += 1;
		}
	}
	
	delete[] tmp_vertices;
	delete[] tmp_indices;
	
	for(int i = 0; i < m_vertexCount; i++)
	{
		printf("%d\n", m_indices[i]);
	}
	
	printf("Vertex count %d\n", m_vertexCount);
	
}


