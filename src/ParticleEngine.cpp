#include "ParticleEngine.h"


ParticleEngine::ParticleEngine(){

	number = 200;
	position = new float*[number];
	for (int i = 0; i<number; i++) position[i] = new float[3];
	
	speed = new float*[number];
	for (int i = 0; i<number; i++) speed[i] = new float[3];
	
	life = new int[number];
	current_particle = 0;
	max_life = 60;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;

}

ParticleEngine::ParticleEngine(int num, int nlife, float r, float g, float b){
	
	number = num;
	position = new float*[number];
	for (int i = 0; i<number; i++) position[i] = new float[3];
	
	speed = new float*[number];
	for (int i = 0; i<number; i++) speed[i] = new float[3];
	
	life = new int[number];
	
	current_particle = 0;
	max_life = nlife;
	color[0] = r;
	color[1] = g;
	color[2] = b;

}

ParticleEngine::~ParticleEngine(){

	for (int i = 0; i<number; i++) {
		delete position[i];
		delete speed[i];
	}
	delete position;
	delete speed;
	delete life;

}

void ParticleEngine::draw(){
	glColor3f(1.0,1.0,1.0);
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
	for (int i = 0; i<number; i++){
	
		if (life[i] > 0) {
			float ratio = (life[i]/(float)max_life);
			glColor3f(color[0]*ratio, color[1]*ratio, color[2]*ratio);
			glVertex3fv(position[i]);
		}
	}
	glEnd();
	glEnable(GL_LIGHTING);
}

void ParticleEngine::update(){
	glm::vec3 s;
	glm::vec3 center(0,0,0);
	for (int i = 0; i<number; i++){
	
		if (life[i] > 0) {
			updatePosition(i); 
			life[i]--;
		}
	}

}

void ParticleEngine::updatePosition(int num){
	position[num][0] += speed[num][0]; 
	position[num][1] += speed[num][1]; 
	position[num][2] += speed[num][2]; 
}

void ParticleEngine::createParticles(int num, glm::vec3 center, glm::vec3 sp, float spread){
	
	if (num > number)num = number;
	if (spread == 0) spread = .01;
	int cnum = 0;
	float x = center.x;
	float y = center.y;
	float z = center.z;
	float sx, sz;
	sx = sp.x;
	sz = sp.z;
	while (cnum<num){
		float rx, rz;
		float rsx, rsz;
		glm::vec2 r = glm::vec2(glm::diskRand(250.0f));
		rx = r[0]/1000.0;
		rz = r[1]/1000.0;
		//float n = (rand()%500)/500.0;
		rsx = r[0]/(spread*1000.0);
		rsz = r[1]/(spread*1000.0);
		if(current_particle>=number) current_particle = current_particle%number;
		position[current_particle][0] = x;
		position[current_particle][1] = y;
		position[current_particle][2] = z;
		life[current_particle] = max_life + rand()%(max_life/3);
		speed[current_particle][0] = sx;
		speed[current_particle][1] = 0;
		speed[current_particle][2] = sz;
		cnum++;
		current_particle++;
	}

}

void ParticleEngine::createSphericalParticles(int num, glm::vec3 center, glm::vec3 sp, float spread){
	
	if (num > number)num = number;
	if (spread == 0) spread = .01;
	int cnum = 0;
	float x = center.x;
	float y = center.y;
	float z = center.z;
	float sx, sy, sz;
	sx = sp.x;
	sy = sp.y;
	sz = sp.z;
	while (cnum<num){
		float rx, ry, rz;
		float rsx, rsy, rsz;
		glm::vec3 r = glm::vec3(glm::ballRand(250.0f));
		rx = r[0]/1000.0;
		ry = r[1]/1000.0;
		rz = r[2]/1000.0;
		//float n = (rand()%500)/500.0;
		rsx = r[0]/(spread*1000.0);
		rsy = r[1]/(spread*1000.0);
		rsz = r[2]/(spread*1000.0);
		if(current_particle>=number) current_particle = current_particle%number;
		position[current_particle][0] = x+rx;
		position[current_particle][1] = y+ry;
		position[current_particle][2] = z+rz;
		life[current_particle] = max_life+ rand()%(max_life/3);
		speed[current_particle][0] = sx+rsx;
		speed[current_particle][1] = sy+rsy;
		speed[current_particle][2] = sz+rsz;
		cnum++;
		current_particle++;
	}

}

void ParticleEngine::createRingOfParticles(int num, glm::vec3 center, glm::vec3 sp, float spread){
	
	if (num > number)num = number;
	if (spread == 0) spread = .01;
	int cnum = 0;
	float x = center.x;
	float z = center.z;
	float sx, sz;
	sx = sp.x;
	sz = sp.z;
	while (cnum<num){
		float rx, rz;
		float rsx, rsz;
		glm::vec2 r = glm::vec2(glm::circularRand(100.0f));
		rx = r[0]/1000.0;
		rz = r[1]/1000.0;
		//float n = (rand()%500)/500.0;
		rsx = r[0]/(spread*1000.0);
		rsz = r[1]/(spread*1000.0);
		if(current_particle>=number) current_particle = current_particle%number;
		position[current_particle][0] = x+rx;
		position[current_particle][1] = 0;
		position[current_particle][2] = z+rz;
		life[current_particle] = max_life+ rand()%(max_life/3);
		speed[current_particle][0] = sx+rsx;
		speed[current_particle][1] = 0;
		speed[current_particle][2] = sz+rsz;
		cnum++;
		current_particle++;
	}

}

void ParticleEngine::createVerticalRingOfParticles(int num, glm::vec3 center, glm::vec3 sp, float spread, float rotation){
	
	
	if (num > number)num = number;
	if (spread == 0) spread = .01;
	int cnum = 0;
	float x = center.x;
	float y = center.y;
	float z = center.z;
	float sx, sy, sz;
	sx = sp.x;
	sy = sp.y;
	sz = sp.z;
	while (cnum<num){
		float rx, ry, rz;
		float rsx, rsy, rsz;
		glm::vec2 r = glm::vec2(glm::circularRand(250.0f));
		rx = r[0]/1000.0 * cos(mradians(rotation));
		ry = r[1]/1000.0;
		rz = r[0]/1000.0 * sin(mradians(rotation));
		//float n = (rand()%500)/500.0;
		rsx = r[0]/(spread*1000.0) * cos(mradians(rotation));
		rsy = r[1]/(spread*1000.0);
		rsz = r[0]/(spread*1000.0) * sin(mradians(rotation));
		if(current_particle>=number) current_particle = current_particle%number;
		position[current_particle][0] = x+rx;
		position[current_particle][1] = y+ry;
		position[current_particle][2] = z+rz;
		life[current_particle] = max_life+ rand()%(max_life/3);
		speed[current_particle][0] = sx+rsx;
		speed[current_particle][1] = sy+rsy;
		speed[current_particle][2] = sz+rsz;
		cnum++;
		current_particle++;
	}


}

void ParticleEngine::createBallParticles(int num, glm::vec3 center, glm::vec3 sp, float spread){
	
	if (num > number)num = number;
	if (spread == 0) spread = .01;
	int cnum = 0;
	float x = center.x;
	float y = center.y;
	float z = center.z;
	float sx, sy, sz;
	sx = sp.x;
	sy = sp.y;
	sz = sp.z;
	while (cnum<num){
		float rx, ry, rz;
		float rsx, rsy, rsz;
		glm::vec3 r = glm::vec3(glm::sphericalRand(250.0f));
		rx = r[0]/1000.0;
		ry = r[1]/1000.0;
		rz = r[2]/1000.0;
		//float n = (rand()%500)/500.0;
		rsx = r[0]/(spread*1000.0);
		rsy = r[1]/(spread*1000.0);
		rsz = r[2]/(spread*1000.0);
		if(current_particle>=number) current_particle = current_particle%number;
		position[current_particle][0] = x+rx;
		position[current_particle][1] = y+ry;
		position[current_particle][2] = z+rz;
		life[current_particle] = max_life+ rand()%(max_life/3);
		speed[current_particle][0] = sx+rsx;
		speed[current_particle][1] = sy+rsy;
		speed[current_particle][2] = sz+rsz;
		cnum++;
		current_particle++;
	}

}
