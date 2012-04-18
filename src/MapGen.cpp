#include "MapGen.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

MapGen::MapGen(){
	srand(time(NULL));
	seed = rand();
}

MapGen::~MapGen(){}

VoxelCube MapGen::genChunk(int x, int y, int z){
	CaveNoise cn;
	HeightNoise hn;
	
	int offset[3] = {x*CHUNK_SIZE - x, y*CHUNK_SIZE - y, z*CHUNK_SIZE - z};
	VoxelCube hndata = hn.noise(CHUNK_SIZE, offset, 1, 1.0, 1.0, seed);
	VoxelCube cndata = cn.noise(CHUNK_SIZE, offset, 1, 1.0, 0.9, seed, 1.0);
	VoxelCube noisedata = hndata - cndata;
	noisedata.addFloor();
	
	return noisedata;
}


