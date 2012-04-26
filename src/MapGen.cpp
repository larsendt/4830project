#include "MapGen.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

MapGen::MapGen(){

}

MapGen::~MapGen(){}

VoxelCube MapGen::genChunk(int x, int y, int z, int seed){
	CaveNoise cn;
	HeightNoise hn;
	
	int offset[3] = {x*CHUNK_SIZE - x, y*CHUNK_SIZE - y, z*CHUNK_SIZE - z};
	VoxelCube hndata = hn.noise(CHUNK_SIZE, offset, 1, 1.0, 1.0, seed);
	VoxelCube cndata = cn.noise(CHUNK_SIZE, offset, 1, 1.0, 0.9, seed, 1.0);
	VoxelCube noisedata = hndata - cndata;

	bool xneg_bound = (x == WORLD_MIN);
	bool xpos_bound = (x == WORLD_MAX-1); 
	bool zneg_bound = (z == WORLD_MIN);
	bool zpos_bound = (z == WORLD_MAX-1); 
	bool yneg_bound = false; // not filling in y gaps
	bool ypos_bound = false;
	
	noisedata.fillBoundaries(xneg_bound, xpos_bound, yneg_bound, ypos_bound, zneg_bound, zpos_bound);
	
	//noisedata.addFloor();
	
	return noisedata;
}


