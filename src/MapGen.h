///////////////
/// MapGen.h
///////////////

#pragma once

#include "CaveNoise.h"
#include "HeightNoise.h"
#include "Types.h"
#include <stdio.h>
#include "VoxelCube.h"

class MapGen{

	public:
		MapGen();
		~MapGen();
		unsigned int shader;
		VoxelCube genChunk(int x, int y, int z, int seed);
};

