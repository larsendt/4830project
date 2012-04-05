//////////////////////////////////////////
///           IEngine.h
//////////////////////////////////////////

#ifndef IEngine_H
#define IEngine_H
#define GL_GLEXT_PROTOTYPES
#include <math.h>
#include "Shader.h"
#include "ObjectLoader.h"
#include "ImageLoader.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include "World.h"
#include "Heightmap.h"
#include "PostProcess.h"
#include "OCL3DFBMNoise.h"
#include "SoftwareMarchingCubes.h"

class IEngine
{
	public:
		IEngine(int argc, char** argv);
		void initGL(int argc, char** argv);
		void checkKeys();
		void drawScene();
		void update();
		void resize(int width, int height);
		int begin();
		float heightFunction(float i, float j);
		void genNoise(int dim);
	private:
		double m_time;
		sf::Window* m_window;
		sf::Clock* m_clock;
		int frames;
		float time;
		float m_updateRate;
		float m_width;
		
		bool m_wireframe;
		
		SoftwareMarchingCubes * mc;
		MeshObject * mo;
		
		PostProcess p;
		Shader * sh;
		
		float pitch; 
		float yaw;
		
		float xpos;
		float ypos;
		float zpos;
};

#endif
