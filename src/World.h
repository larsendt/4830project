#pragma once

#include <vector>
#include <map>
#include "Chunk.h"
#include "MapGen.h"

class World{
	
	public:

		World();
		World(int size);
		~World();
	
		Chunk * getChunkAt(int x, int y, int z);
		void drawAt(int x, int y, int z);
		MapGen m_gen;
		
		void setSeed(int seed) { m_seed = seed; }
	
	private:
		int m_seed;
		int max_size;
		int cur_size;
		Chunk ** chunks;
	
};
