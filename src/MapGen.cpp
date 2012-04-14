#include "MapGen.h"
#include <stdio.h>

MapGen::MapGen(){}

MapGen::~MapGen(){}

VoxelCube MapGen::genChunk(int x, int y, int z){
	CaveNoise cn;
	HeightNoise hn;
	
	int offset[3] = {x*CHUNK_SIZE, y*CHUNK_SIZE, z*CHUNK_SIZE};
	VoxelCube hndata = hn.noise(CHUNK_SIZE, offset, 1, 1.0, 1.0, 0);
	VoxelCube cndata = cn.noise(CHUNK_SIZE, offset, 1, 1.0, 0.9, 0, 1.0);
	VoxelCube noisedata = hndata - cndata;
	noisedata.addFloor();
	
	return noisedata;
}


