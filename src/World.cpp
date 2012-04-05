#include "World.h"

World::World(){
	max_size = 20;
}

World::~World(){

}

World::World(int size){

	max_size = size;
	cur_size = 0;

}

Chunk* World::getChunkAt(int x, int y, int z){

	for (int i = 0; i<cur_size; i++){
	
		Chunk* it = chunks[i];
		if ((it->x == x) && (it->x == x) && (it->x == x)){
			return it;
		}
	
	}
	if (cur_size == max_size){
	
		return NULL;
	
	}
	Chunk * c = new Chunk(x,y,z);
	chunks[cur_size] = c;
	cur_size ++;
	return c;
	
}

void World::drawAt(int x, int y, int z){
	for (int ix = -2; ix < 2; ix++){
		for (int iy = -2; iy < 2; iy++){
			for (int iz = -2; iz < 2; iz++){
			
				Chunk * c = getChunkAt(ix, iy, iz);
				if (c!=NULL) c->draw();
				
			}
		}
	}
}
