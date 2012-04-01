#include "SpriteEngine.h"

#ifndef RADIAL_S_ENGINE
#define RADIAL_S_ENGINE

class RadialSEngine: public SpriteEngine{

	public:
		RadialSEngine();
		RadialSEngine(int n, int l, float r, float g, float b);
		glm::vec3 center;
		void update();

};

#endif
