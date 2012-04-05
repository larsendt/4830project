#include "MeshObject.h"
#include "CollisionMesh.h"

class Chunk{
	public:
		Chunk();
		~Chunk();
		Chunk(int x, int y, int z);
		void draw();
	//private:
		int x;
		int y; 
		int z;
		MeshObject * m;
		CollisionMesh * cm;
};
