#include "Chunk.h"
#include <stdio.h>

Chunk::Chunk(){
	printf("Chunk initialized without any data, what's wrong with you\n");
	exit(0);
}

Chunk::~Chunk(){

	delete m;

}

Chunk::Chunk(int nx, int ny, int nz, MapGen * mgen){
	x = nx; y = ny; z = nz;
	gen = mgen;
	make();
	printf("All made & stuff\n");
}

void Chunk::make(){
	VoxelCube noise_data = gen->genChunk(x,y,z);
	m = new MeshObject();
	m->setShader(gen->shader);
	convertToMesh(m, noise_data, CHUNK_SIZE, 1.0, 64);
}

void Chunk::draw(){
	m->draw();
}
