#include "World.h"

World::World(){
	max_size = 50;
	cur_size = 0;
	chunks = new Chunk * [max_size];
}

World::~World(){

}

World::World(int size){

	max_size = size;
	cur_size = 0;
	
	chunks = new Chunk * [size];
}

Chunk* World::getChunkAt(int x, int y, int z){

	for (int i = 0; i<cur_size; i++){
	
		Chunk* it = chunks[i];
		if ((it->x == x) && (it->y == y) && (it->z == z)){
			return it;
		}
	
	}
	if (cur_size == max_size){
	
		return NULL;
	
	}
	Chunk * c = new Chunk(x,y,z, &m_gen);
	chunks[cur_size] = c;
	cur_size ++;
	return c;
	
}

void World::drawAt(int x, int y, int z){
	for (int ix = 0; ix < 6; ix++){
		for (int iy = 0; iy < 1; iy++){
			for (int iz = 0; iz < 6; iz++){
				//printf("%i %i %i\n",ix,iy,iz);
				Chunk * c = getChunkAt(ix, iy, iz);
				//printf("Chunk done got\n");
				glPushMatrix();
				glTranslatef(ix*(CHUNK_SIZE-1),iy*(CHUNK_SIZE-1),iz*(CHUNK_SIZE-1));
				if (c!=NULL) c->draw();
				glPopMatrix();
				
			}
		}
	}
}
