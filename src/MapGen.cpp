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

	bool xneg_bound = (x == 0);
	bool xpos_bound = (x == 2); // change this if world dimensions change
	bool zneg_bound = (z == 0);
	bool zpos_bound = (z == 2); // also change this
	bool yneg_bound = false; // not filling in y gaps
	bool ypos_bound = false;
	
	noisedata.fillBoundaries(xneg_bound, xpos_bound, yneg_bound, ypos_bound, zneg_bound, zpos_bound);
	
	//noisedata.addFloor();
	
	return noisedata;
}


