#include <SFML/Graphics.hpp>
#include "MeshObject.h"
#include "Perlin.h"

#define Uint8 sf::Uint8

struct COORD3D{
	float x;
	float y;
	float z;
};

struct COORD2D{
	float s;
	float t;
};

struct VERT{
	COORD3D c;
	COORD3D n;
	COORD2D xy;
	COORD2D xz;
	COORD2D yz;
	unsigned int pos;
};

struct TRIANGLE{
	VERT * a;
	VERT * b;
	VERT * c;
};

class Heightmap{

	public:
		Heightmap();
		Heightmap(int width, int height);
		
		MeshObject * convertToMesh();
		void draw();
		void create();
		void writeToImage();
		float heightFunction(float x, float z);
		void setShader(unsigned int program);
	private:
		unsigned int shader;
		int h_width;
		int h_height;
		int t_num;
		Perlin * perlin;
		VERT *** vertices;
		TRIANGLE ** triangles; 
};
