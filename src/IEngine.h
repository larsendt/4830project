//////////////////////////////////////////
///           IEngine.h
//////////////////////////////////////////

#pragma once

#define GL_GLEXT_PROTOTYPES
#include <math.h>
#include "Shader.h"
#include "ObjectLoader.h"
#include "ImageLoader.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include "World.h"
#include "PostProcess.h"
#include "Vec3.h"
#include "Water.h"
#include "Skybox.h"

#define PI 3.1415
#define mradians(i) (i/180.0 * PI)
#define mdegrees(i) (i/PI * 180.0)

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
	private:
		sf::Window* m_window;
		sf::Clock* m_clock;
		int frames;
		float m_time;
		float m_updateRate;
		float m_width;
		
		bool m_wireframe;
		
		int m_seed;
		
		World w;
		Skybox* skybox;
		
		PostProcess p;
		Shader * sh;
		Shader * sh2;
		Shader * waterShader;
		Water * water;
		float pitchspeed;
		float pitch;
		float yawspeed; 
		float yaw;
		
		vec3 c_pos;
		vec3 c_speed;
		
		GLuint tex, tex2, tex3;
};
