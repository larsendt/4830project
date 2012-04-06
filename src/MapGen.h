///////////////
/// MapGen.h
///////////////

#include "OCL3DFBMNoise.h"
#include "Types.h"
#include <stdio.h>

#ifndef MAPGEN
#define MAPGEN

class MapGen{

	public:
		MapGen();
		~MapGen();
		unsigned int shader;
		unsigned char * genChunk(int x, int y, int z);
	private:
		OCL3DFBMNoise m_n;
};

#endif
