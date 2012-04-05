#include "RadialSEngine.h"

RadialSEngine::RadialSEngine(){

	number = 200;
	position = new float*[number];
	for (int i = 0; i<number; i++) position[i] = new float[3];
	
	speed = new float*[number];
	for (int i = 0; i<number; i++) speed[i] = new float[3];
	
	life = new int[number];
	current_particle = 0;
	max_life = 60;
	size = .5;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
	center = glm::vec3(0,0,0);

}

RadialSEngine::RadialSEngine(int num, int nlife, float r, float g, float b){
	
	number = num;
	position = new float*[number];
	for (int i = 0; i<number; i++) position[i] = new float[3];
	
	speed = new float*[number];
	for (int i = 0; i<number; i++) speed[i] = new float[3];
	
	life = new int[number];
	size = .7;
	current_particle = 0;
	max_life = nlife;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	center = glm::vec3(0,0,0);
}

void RadialSEngine::update(){
	glm::vec3 s;
	for (int i = 0; i<number; i++){
	
		if (life[i] > 0) {
			s.x = center.x - position[i][0];
			s.y = center.y - position[i][1];
			s.z = center.z - position[i][2];
			s = glm::normalize(s);
			speed[i][0] += s.x*.0001;
			speed[i][1] += s.y*.0001;
			speed[i][2] += s.z*.0001;
			updatePosition(i); 
			life[i]--;
		}
	}

}
