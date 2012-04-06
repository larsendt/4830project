#include <vector>
#include <map>
#include "Chunk.h"
#include "MapGen.h"

#ifndef WORLD
#define WORLD

class World{
	
	public:

		World();
		World(int size);
		~World();
	
		Chunk * getChunkAt(int x, int y, int z);
		void drawAt(int x, int y, int z);
		MapGen m_gen;
	
	private:
		
		int max_size;
		int cur_size;
		Chunk ** chunks;
	
};

#endif
