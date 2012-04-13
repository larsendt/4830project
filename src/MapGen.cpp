#include "MapGen.h"

MapGen::MapGen(){}

MapGen::~MapGen(){}

VoxelCube MapGen::genChunk(int x, int y, int z){
	CaveNoise cn;
	HeightNoise hn;
	
	int offset[3] = {x, y, z};
	VoxelCube hndata = hn.noise(CHUNK_SIZE, offset, 1, 1.0, 1.0, 0);
	VoxelCube cndata = cn.noise(CHUNK_SIZE, offset, 1, 2.0, 2.0, 0, 1.0);
	VoxelCube noisedata = hndata - cndata;
	noisedata.addFloor();
	
	return noisedata;
}


