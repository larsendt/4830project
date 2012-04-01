
#ifndef PARTICLES
#define PARTICLES

#define NUM_PARTICLES 200

#define mradians(i) ((i)*PI/180)
#define mdegrees(i) ((i)*180/PI)
#ifndef MATH
	#define MATH
	#include <math.h>
#endif
#ifndef PI
	#define PI 3.14159265
#endif

#include <stdlib.h>
#include <GL/gl.h>
#include <stdio.h>
#include "ext/glm/glm.hpp"
#include "ext/glm/gtc/random.hpp"
#include "ext/glm/gtx/noise.hpp"

class ParticleEngine{

	public:
		ParticleEngine();
		ParticleEngine(int num, int nlife, float r, float g, float b);
		~ParticleEngine();
		float ** position;	
		float ** speed;
		int  * life;
		virtual void draw();
		void update();
		void updatePosition(int num);
		void createParticles(int num, glm::vec3 center, glm::vec3 speed, float spread);
		void createSphericalParticles(int num, glm::vec3 center, glm::vec3 speed, float spread);
		void createRingOfParticles(int num, glm::vec3 center, glm::vec3 sp, float spread);
		void createVerticalRingOfParticles(int num, glm::vec3 center, glm::vec3 sp, float spread, float rotation);
		void createBallParticles(int num, glm::vec3 center, glm::vec3 speed, float spread);
		int current_particle;
		int max_life;
		int number;
		float color[3];
};

#endif
