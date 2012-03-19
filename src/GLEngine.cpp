#include "GLEngine.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Texture.h"


GLEngine::GLEngine(int argc, char** argv)
{
	(void) argc;
	(void) argv;
	
	fprintf(stdout, "Initializing GLEngine\n");
	initGL(argc, argv);
}

GLEngine::~GLEngine()
{
	delete m_window;
	delete m_clock;
}

void GLEngine::initGL(int argc, char** argv)
{
	m_window = new sf::Window(sf::VideoMode(512, 512), "GLEngine");
	m_clock = new sf::Clock();
	m_width = m_window->GetWidth();
	m_height = m_window->GetHeight();
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
	
	m_texSize = 2048;
	m_perlin = new OCLNoise();
	m_texData = new unsigned char[m_texSize * m_texSize * 4];
	m_perlin->noise2D(GRADIENT, m_texSize, m_texData);
	m_texture = Texture::loadFromMemory(m_texSize, m_texSize, m_texData);
	m_currentNoiseType = 0;
	
	m_rotation = 0;
	m_mouseRotX = 0;
	m_mouseRotY = 0;
	m_mouseLastX = 0;
	m_mouseLastY = 0;
	
	m_updateRate = 1.0/60.0;
	resize(m_width, m_height);
}

int GLEngine::begin()
{
	while(m_window->IsOpened())
	{
		sf::Event Event;
		while(m_window->GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
			{
				m_window->Close();
				return 0;
			}
			else if(Event.Type == sf::Event::MouseButtonPressed)
			{
			    m_mouseLastX = Event.MouseButton.X;
			    m_mouseLastY = Event.MouseButton.Y;
		    }
		    else if(Event.Type == sf::Event::MouseMoved && m_window->GetInput().IsMouseButtonDown(sf::Mouse::Left))
		    {
		        int dx = Event.MouseMove.Y - m_mouseLastY; 
		        int dy = Event.MouseMove.X - m_mouseLastX;
		        m_mouseRotX += dx;
		        m_mouseRotY += dy;
		        m_mouseLastX = Event.MouseMove.X;
		        m_mouseLastY = Event.MouseMove.Y;
	        }
	        else if(Event.Type == sf::Event::MouseWheelMoved)
	        {
	            m_scale += (float)Event.MouseWheel.Delta / 10.0;
            }
			else if(Event.Type == sf::Event::KeyPressed)
			{
				switch(Event.Key.Code)
				{
					case sf::Key::Escape:
						m_window->Close();
						return 0;
					case sf::Key::Space:
						m_currentNoiseType = (m_currentNoiseType + 1) % 5;
						regenNoise();
						break;
					default:
						break;
				}
			}
			else if(Event.Type == sf::Event::Resized)
			{
				resize(Event.Size.Width, Event.Size.Height);
			}
		}
		
		update();
		drawScene();
		m_window->Display();
	}
	return 0;
}


void GLEngine::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
  	glBindTexture(GL_TEXTURE_2D, m_texture);
  	glBegin(GL_POLYGON);
  	glTexCoord2f(0, 0); glVertex3f(-m_aspectRatio, -1, 0);
  	glTexCoord2f(1, 0); glVertex3f(m_aspectRatio, -1, 0);
  	glTexCoord2f(1, 1); glVertex3f(m_aspectRatio, 1, 0);
  	glTexCoord2f(0, 1); glVertex3f(-m_aspectRatio, 1, 0);
  	glEnd();
}


void GLEngine::update()
{
	float time = m_clock->GetElapsedTime();
	float multiplier = 1.0;
		
	if(time < m_updateRate)
	{
		return;
	}
	else if(time > m_updateRate)
	{
		multiplier = time / m_updateRate;
	}
	
	m_clock->Reset();
}


void GLEngine::resize(int width, int height)
{
	m_aspectRatio = (height>0) ? (GLfloat)width/height : 1;
	m_width = width;
	m_height = height;
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-m_aspectRatio, +m_aspectRatio, -1.0, +1.0, -10.0, +10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLEngine::regenNoise()
{
	NoiseType type;
	
	switch(m_currentNoiseType)
	{
		case 0:
			type = GRADIENT;
			printf("Current noise type: 2D Gradient\n");
			break;
		case 1:
			type = FBM;
			printf("Current noise type: 2D Fractional Brownian Motion\n");
			break;
		case 2:
			type = TURBULENCE;
			printf("Current noise type: 2D Turbulence\n");
			break;
		case 3:
			type = MONOFRACTAL;
			printf("Current noise type: 2D Mono-Fractal\n");
			break;
		case 4:
			type = MULTIFRACTAL;
			printf("Current noise type: 2D Ridged Multi-Fractal\n");
			break;
		default:
			printf("Current noise type: 2D Gradient\n");
			type = GRADIENT;
	}
	
	m_perlin->noise2D(type, m_texSize, m_texData);
	Texture::deleteTexture(m_texture);
	m_texture = Texture::loadFromMemory(m_texSize, m_texSize, m_texData);
}

