#include "ImageLoader.h"

GLuint loadImage(char* file){

	sf::Image img;
	if (!img.LoadFromFile(file)){
		printf("Couldn't load %s\n", file);
	}
	GLuint texture;
	 //  Generate 2D texture
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
   //  Copy image
	//glTexImage2D(GL_TEXTURE_2D,0,4,img.GetWidth(),img.GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,img.GetPixelsPtr());
	
	// instead build mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.GetWidth(), img.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, img.GetPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	return texture;

}

void bindImage(GLuint img){

	glBindTexture(GL_TEXTURE_2D,img);
}
