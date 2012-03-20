#include "HeightMap.h"
#include <stdio.h>

HeightMap::HeightMap()
{
	m_noise = new OCLNoise();
	m_vbo = new VertexBufferObject();
	m_kernel = new OCLKernel("kernels/heightmap.cl", "generate_heightmap");
	m_currentNoiseIndex = -1;
	m_dim = 8;
	m_spacing = 0.01;
	
	m_numVertices = m_dim * m_dim * 3;
	m_numIndices = (m_dim-1) * (m_dim-1) * 6;
	
	m_noiseMap = new unsigned char[m_dim * m_dim * 4];
	m_vertices = new float[m_numVertices];
	m_normals = new float[m_numVertices];
	m_indices = new unsigned int[m_numIndices];
	m_interleaved = new Vertex[m_numVertices/3];
	nextHeightMap();
}

HeightMap::~HeightMap()
{
	delete m_noise;
	delete m_vbo;
	delete m_kernel;
	delete[] m_noiseMap;
	delete[] m_vertices;
	delete[] m_normals;
	delete[] m_indices;
	delete[] m_interleaved;
}

void HeightMap::nextHeightMap()
{
	m_currentNoiseIndex = (m_currentNoiseIndex + 1) % 5;
	
	NoiseType type;
	switch(m_currentNoiseIndex)
	{
		case 0:
			type = GRADIENT;
			printf("Current noise type: 2D Gradient\n");
			break;
		case 1:
			type = FBM;
			printf("Current noise type: 2D Fractional Brownian Motion\n");
			break;
		case 2:
			type = TURBULENCE;
			printf("Current noise type: 2D Turbulence\n");
			break;
		case 3:
			type = MONOFRACTAL;
			printf("Current noise type: 2D Mono-Fractal\n");
			break;
		case 4:
			type = MULTIFRACTAL;
			printf("Current noise type: 2D Ridged Multi-Fractal\n");
			break;
		default:
			printf("Current noise type: 2D Gradient\n");
			type = GRADIENT;
	}

	for(int i = 0; i < m_numVertices; i++)
	{
		m_vertices[i] = 0;
	}

	m_noise->noise2D(type, m_dim, m_noiseMap);
	
	// run heightmap.cl here
	OCLArgument args[6];
	OCLArgument read_buffers[3];
	OCLArgument write_buffers[1];
	
	OCLArgument a;
	
	a.data = m_noiseMap;
	a.byte_size = m_dim * m_dim * 4 * sizeof(unsigned char);
	a.is_buffer = true;
	a.buffer_index = 0;
	
	args[0] = a;
	write_buffers[0] = a;
	
	a.data = m_vertices;
	a.byte_size = m_numVertices * sizeof(float);
	a.is_buffer = true;
	a.buffer_index = 0;
	
	args[1] = a;
	read_buffers[0] = a;
	
	a.data = m_normals;
	a.byte_size = m_numVertices * sizeof(float);
	a.is_buffer = true;
	a.buffer_index = 1;
	
	args[2] = a;
	read_buffers[1] = a;
	
	a.data = m_indices;
	a.byte_size = m_numIndices * sizeof(unsigned int);
	a.is_buffer = true;
	a.buffer_index = 2;
	
	args[3] = a;
	read_buffers[2] = a;
	
	a.data = &m_dim;
	a.byte_size = sizeof(m_dim);
	a.is_buffer = false;
	
	args[4] = a;
	
	a.data = &m_spacing;
	a.byte_size = sizeof(m_spacing);
	a.is_buffer = false;
	
	args[5] = a; 
	
	m_kernel->run(6, args, 1, write_buffers, 3, read_buffers, m_dim, m_dim);
	
	for(int i = 0; i < m_numIndices; i+=3)
	{
		printf("%d\n", m_indices[i]);
	}
	
	for(int i = 0; i < m_numVertices; i+=3)
	{
		Vertex v;
		v.coord[0] = m_vertices[i];
		v.coord[1] = m_vertices[i+1];
		v.coord[2] = m_vertices[i+2];
		v.normal[0] = m_normals[i];
		v.normal[1] = m_normals[i+1];
		v.normal[2] = m_normals[i+2];
		m_interleaved[i/3] = v;
	}
	
	m_vbo->clear();
	m_vbo->setData(m_numIndices, m_interleaved, m_indices);
	
}

void HeightMap::draw()
{
	m_vbo->draw();
}


