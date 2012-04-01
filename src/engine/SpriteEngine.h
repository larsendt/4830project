#include "ParticleEngine.h"

#ifndef SPRITEENGINE
#define SPRITEENGINE
class SpriteEngine: public ParticleEngine{

	public:
		SpriteEngine();
		SpriteEngine(int num, int nlife, float r, float g, float b);
		float size;
		void draw();
		unsigned int tex;
};

#endif
