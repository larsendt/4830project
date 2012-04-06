//////////////////////////////////////////
///           IEngine.h
//////////////////////////////////////////

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


#ifndef IEngine_H
#define IEngine_H

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
		double m_time;
		sf::Window* m_window;
		sf::Clock* m_clock;
		int frames;
		float time;
		float m_updateRate;
		float m_width;
		
		bool m_wireframe;
		
		World w;
		
		PostProcess p;
		Shader * sh;
		
		float pitchspeed;
		float pitch;
		float yawspeed; 
		float yaw;
		
		vec3 c_pos;
		vec3 c_speed;
};

#endif
