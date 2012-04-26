#include "Chunk.h"
#include <stdio.h>

Chunk::Chunk(){
	printf("Chunk initialized without any data, what's wrong with you\n");
	exit(0);
}

Chunk::~Chunk(){

	delete m;

}

Chunk::Chunk(int nx, int ny, int nz, MapGen * mgen, int seed){
	x = nx; y = ny; z = nz;
	gen = mgen;
	m_seed = seed;
	make();
	printf("All made & stuff\n");
}

void Chunk::make(){
	VoxelCube noise_data = gen->genChunk(x,y,z, m_seed);
	m = new MeshObject();
	m->setShader(gen->shader);
	convertToMesh(m, noise_data, CHUNK_SIZE, 1.0, 192);
}

void Chunk::draw(){
	m->draw();
}
