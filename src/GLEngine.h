#ifndef GLENGINE_H
#define GLENGINE_H

#include <SFML/Window.hpp>
#include <vector>
#include "OCLNoise.h"

class GLEngine
{
	public:
		GLEngine(int argc, char** argv);
		~GLEngine();
		
		void initGL(int argc, char** argv);
		void drawScene();
		void update();
		void resize(int width, int height);
		int begin();
		
	private:
		void reperlin();
	
		sf::Window* m_window;
		sf::Clock* m_clock;
		OCLNoise* m_perlin;
		GLuint m_texture;
		unsigned char* m_texData;
		int m_texSize;

		float m_updateRate;
		float m_aspectRatio;
		int m_width;
		int m_height;
		float m_rotation;
		int m_mouseLastX;
		int m_mouseLastY;
        float m_mouseRotX;
        float m_mouseRotY;
        float m_scale;
        
};

#endif
