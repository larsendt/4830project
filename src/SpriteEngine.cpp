#include "SpriteEngine.h"

SpriteEngine::SpriteEngine(){

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

}

SpriteEngine::SpriteEngine(int num, int nlife, float r, float g, float b){
	
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

}

void SpriteEngine::draw(){
	glColor3f(1.0,1.0,1.0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
	glDisable(GL_CULL_FACE);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
	
	for (int i = 0; i<number; i++){
	
		if (life[i] > 0) {
			float ratio = life[i]/(float)max_life;
			if (ratio>1) ratio =1;
			float asize = size+(3*size) - ratio*(3*size);
			glColor4f(color[0]*(ratio*.1),color[1]*(ratio*.1),color[2]*(ratio*.1),ratio*.1);
			glTexCoord2f(1,1);glVertex3f(position[i][0] + asize, position[i][1], position[i][2] + asize);
			glTexCoord2f(0,1);glVertex3f(position[i][0] - asize, position[i][1], position[i][2] + asize);
			glTexCoord2f(0,0);glVertex3f(position[i][0] - asize, position[i][1], position[i][2] - asize);
			glTexCoord2f(1,0);glVertex3f(position[i][0] + asize, position[i][1], position[i][2] - asize);
		}
	}
	glEnd();
	glEnable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}
