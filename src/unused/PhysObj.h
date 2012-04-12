#include "ext/glm/glm.hpp"
#include "Collision.h"
#include "ParticleEngine.h"
//#define DEBUG
#ifndef PHYS_OBJ
#define PHYS_OBJ

class PhysObj{
	public:
		PhysObj();
		PhysObj(glm::vec3 pos, glm::vec3 vel, float rad);
		void addForce(glm::vec3 dir, float amount);
		void update();
		void draw();
		void checkLineCollide(glm::vec3 pa, glm::vec3 pb, glm::vec3 pnorm);
		bool checkTriCollide(glm::vec3 ta, glm::vec3 tb, glm::vec3 tc, glm::vec3 tnorm);
		glm::vec3 m_pos;
		glm::vec3 m_vel;
		ParticleEngine* pengine;
		bool moving;
		int name;
		float mass;
		float m_rad;
		float bounciness;
};
#endif
