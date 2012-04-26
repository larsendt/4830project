#pragma once

#include "MeshObject.h"
#include "Polygonize.h"
#include "MapGen.h"
#include "Types.h"

class Chunk{
	public:
		Chunk();
		~Chunk();
		Chunk(int nx, int ny, int nz, MapGen* gen, int seed);
		
		void draw();
		
		int x;
		int y; 
		int z;
	private:
		MapGen* gen;
		MeshObject * m;
		int m_seed;
		void make();
};
