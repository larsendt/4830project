#pragma once

#include "MeshObject.h"
#include "Polygonize.h"
#include "MapGen.h"
#include "Types.h"

class Chunk{
	public:
		Chunk();
		~Chunk();
		Chunk(int nx, int ny, int nz, MapGen* gen);
		
		void draw();
		
		int x;
		int y; 
		int z;
	private:
		MapGen* gen;
		MeshObject * m;
		void make();
};
