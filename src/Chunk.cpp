#include "Chunk.h"

Chunk::Chunk(){
	printf("Chunk initialized without any data, what's wrong with you\n");
	exit(0);
}

Chunk::~Chunk(){

	delete m;

}

Chunk::Chunk(int nx, int ny, int nz, MapGen * mgen){
	x = nx; y = ny; z = nz;
	gen = mgen;
	make();
	printf("All made & stuff\n");
}

void Chunk::make(){
	
	unsigned char * n_data = gen->genChunk(x,y,z);
	
	for (int i = 0; i<CHUNK_SIZE; i++){
		int xind = (CHUNK_SIZE * CHUNK_SIZE * i); 
		for (int j = 0; j<CHUNK_SIZE;j++){
			int yind = CHUNK_SIZE * j;
			for (int k = 0; k<CHUNK_SIZE; k++){
				int index = xind + yind + k;
				
			}
		}
	}
	
	m = new MeshObject();
	m->setShader(gen->shader);
	convertToMesh(m, n_data, CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE,1.0,172);
	delete n_data;
}

void Chunk::draw(){
	m->draw();
}
