#include "MapGen.h"

MapGen::MapGen(){}

MapGen::~MapGen(){}

unsigned char * MapGen::genChunk(int x, int y, int z){

	
	int size = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
	unsigned char * n_data = new unsigned char[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	float pos[3] = {x,y,z};
	
	if (!m_n.noise(CHUNK_SIZE, n_data, pos)){
		fprintf(stderr, "Noise gen failed\n");
		exit(1);
	}
	
	return n_data;
	
}


