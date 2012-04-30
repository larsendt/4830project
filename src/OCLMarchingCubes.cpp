#include "OCLMarchingCubes.h"
#include "OCLKernel.h"
#include <stdio.h>


MeshObject * oclConvertToMesh(MeshObject * mesh, VoxelCube voxels, int dim, float spacing, unsigned char isolevel)
{
	OCLKernel* kernel = new OCLKernel("kernels/marching_cubes.cl", "generateMesh");
	
	int max_vxs = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 16;
	VERTEX* vertices = new VERTEX[max_vxs];
	unsigned char* valid = new unsigned char[max_vxs];
	
	OCLArgument args[6];
	OCLArgument buffers[3];
	
	OCLArgument a;
	a.data = voxels.data();
	a.byte_size = voxels.count() * sizeof(unsigned char);
	a.is_buffer = true;
	a.buffer_type = WRITE;
	a.buffer_index = 0;
	args[0] = a;	
	buffers[0] = a;

	a.data = vertices;
	a.byte_size = max_vxs * sizeof(*vertices);
	a.is_buffer = true;
	a.buffer_type = READ;
	a.buffer_index = 1;
	args[1] = a;
	buffers[1] = a;
	
	a.data = valid;
	a.byte_size = max_vxs * sizeof(*valid);
	a.is_buffer = true;
	a.buffer_type = READ;
	a.buffer_index = 2;
	args[2] = a;
	buffers[2] = a;
	
	a.data = &dim;
	a.byte_size = sizeof(dim);
	a.is_buffer = false;
	args[3] = a;
	
	a.data = &spacing;
	a.byte_size = sizeof(spacing);
	a.is_buffer = false;
	args[4] = a;
	
	a.data = &isolevel;
	a.byte_size = sizeof(isolevel);
	a.is_buffer = false;
	args[5] = a;
	
	if(!kernel->run(6, args, 3, buffers, CHUNK_SIZE-1, CHUNK_SIZE-1))
	{
		fprintf(stderr, "Error: marching cubes borked...\n");
		exit(1);
	}
	
	int newmax = 32;
	int vx_count = 0;
	VERTEX* scrubbed_vertices = (VERTEX*) malloc(newmax * sizeof(VERTEX));
	GLuint* scrubbed_indices = (GLuint*) malloc(newmax * sizeof(GLuint));
	
	for(int i = 0; i < max_vxs; i++)
	{
		// 255 is a magic number. don't touch
		if(valid[i] == 255)
		{
			//printf("%d %.2f %.2f %.2f\n", valid[i], vertices[i].c.x, vertices[i].c.y, vertices[i].c.z);

			//if((vx_count+1) % 3 == 0)
			//{
			//	printf("================\n");
			//}

			if(vx_count >= newmax)
			{
				newmax *= 2;
				scrubbed_vertices = (VERTEX*) realloc(scrubbed_vertices, newmax * sizeof(VERTEX));
				scrubbed_indices = (GLuint*) realloc(scrubbed_indices, newmax * sizeof(GLuint));
			}
			
			scrubbed_vertices[vx_count] = vertices[i];
			scrubbed_indices[vx_count] = vx_count;
			vx_count += 1;
		}
	}
	
	
	delete[] vertices;
	delete[] valid;
	
	printf("OCLMarchingCubes: %d vertices set out of a possible %d (%.3f%% fill)\n", vx_count, dim*dim*dim*12, ((float)vx_count/(dim*dim*dim*12))*100);	
	
	mesh->setInterleaved(scrubbed_vertices, vx_count-1, scrubbed_indices, vx_count-1);
	return mesh;
}





