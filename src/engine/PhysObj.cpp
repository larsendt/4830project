#include "PhysObj.h"

PhysObj::PhysObj(){
	m_vel = glm::vec3(0,0,0);
	m_pos = glm::vec3(0,0,0);
	m_rad = 1;
	bounciness = .7;
	mass = 1;
	name = 0;
}

PhysObj::PhysObj(glm::vec3 pos, glm::vec3 vel, float rad){
	m_pos = pos; m_vel = vel; m_rad = rad;
	bounciness = .7;
	mass = 1;
	name = 0;
}

void PhysObj::addForce(glm::vec3 dir, float amount){
	m_vel += (dir*amount)/mass;	
	
}

void PhysObj::update(){
	
	m_pos += m_vel;
}

void PhysObj::draw(){
	glPushMatrix();
	glColor3f(0,1,0);
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glScalef(m_rad, m_rad, m_rad);
	glCallList(name);
	glPopMatrix();
}

void PhysObj::checkLineCollide(glm::vec3 pa, glm::vec3 pb, glm::vec3 pnorm){
	/*// intersect takes in the object position (m_pos), the normalized sphere intesection point (which is given by -pnorm), a point on the line (pa), and the normal of the line (pnorm);
	if (glm::dot(glm::normalize(m_vel), pnorm) > 0) return;
	float b = intersect(m_pos+m_vel, -pnorm, pa, pnorm); // refer to the top comment
	
	// cpoL finds the closest point on the line, given the position and velocity 
	glm::vec3 cpol;
	if (b<0) return;
	if (b>m_rad) {// No intersection
		return;
	}
	if(!cpoLine(pa, pb, m_pos+m_vel, cpol) )return;
	
	else { 
		m_pos = cpol - (-pnorm * m_rad); // sets it on the line at the intersect point
		pengine->createSphericalParticles(15, cpol, pnorm*.8f, 10);
		m_vel = m_vel - (1+bounciness)*((glm::dot(m_vel,pnorm)*pnorm));
		
	}*/
}

bool PhysObj::checkTriCollide(glm::vec3 ta, glm::vec3 tb, glm::vec3 tc, glm::vec3 tnorm){
	float test = glm::dot(m_vel, tnorm);
	if (test > 0) {
		return false; // normal faces away from velocity
	}
	glm::vec3 colPoint;
	float dist;
	bool collide = checkCollide(tnorm, m_pos, m_vel, ta, tb, tc, colPoint, dist);
	
	if (collide){
		
		//m_pos = colPoint+tnorm;
		m_vel = m_vel - (1+bounciness)*((glm::dot(m_vel,tnorm)*tnorm));
		if (acos(glm::dot(tnorm,glm::vec3(0,-1,0))) > (7*PI/8.0)){
			// do friction
			if (!moving){
				float l = glm::length(m_vel);
			
				if (l < .05){
					m_vel = glm::vec3(0,0,0); 
				
				}
				else{
					float prevy = m_vel.y;
					glm::vec3 nv = glm::normalize(m_vel);
					m_vel = nv * (l - .05f);
					m_vel.y = prevy;
					
				}
			}
		}
		
		return true;
	}
	return false;
 	
}
