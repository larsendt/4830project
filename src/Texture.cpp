#include "Texture.h"
#include <stdio.h>
#include <stdlib.h>

Texture::Texture()
{

}


static std::map<std::string, GLuint> m_texMap;

GLuint Texture::loadTexture(std::string img_path)
{
	if(m_texMap.find(img_path) != m_texMap.end())
	{
		//printf("%s was already loaded. Returning existing texture handle.\n", img_path);
		return m_texMap[img_path];
	}

    sf::Image* img = new sf::Image();
    if(!img->LoadFromFile(img_path))
    {
        fprintf(stderr, "Failed to load texture: %s Using default color #ff00ff\n", img_path.c_str());
		img->Create(50, 50, sf::Color::Magenta);	
    }
    
    glEnable(GL_TEXTURE_2D);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->GetWidth(), img->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img->GetPixelsPtr());
    glBindTexture(GL_TEXTURE_2D, 0);
    
	delete img;    
	m_texMap[img_path] = texture;
    return texture;
}

GLuint Texture::loadFromMemory(int width, int height, unsigned char* data)
{
	glEnable(GL_TEXTURE_2D);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

void Texture::deleteTexture(GLuint texture_handle)
{
	glDeleteTextures(1, &texture_handle);
}
