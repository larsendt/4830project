#include "Skybox.h"
#include "Texture.h"
#include <stdio.h>

Skybox::Skybox()
{
	m_tex = Texture::loadTexture("tex/sky.png");
	
	m_displayList = glGenLists(1);
	
	m_sphere = gluNewQuadric();
	gluQuadricDrawStyle(m_sphere, GLU_FILL);
	gluQuadricTexture(m_sphere, true);
	gluQuadricNormals(m_sphere, GLU_SMOOTH);
	
	glNewList(m_displayList, GL_COMPILE);
	
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glUseProgram(0);
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	gluSphere(m_sphere, 500.0, 20, 20);
	
	glPopMatrix();
	glEndList();
	
	gluDeleteQuadric(m_sphere);

}

void Skybox::draw()
{
	glCallList(m_displayList);
}
