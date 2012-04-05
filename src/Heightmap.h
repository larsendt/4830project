#include <SFML/Graphics.hpp>
#include "MeshObject.h"
#include "Perlin.h"
#include "Types.h"

#define Uint8 sf::Uint8


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
		VERTEX *** vertices;
		TRIANGLE ** triangles; 
};
