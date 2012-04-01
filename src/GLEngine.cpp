#include "GLEngine.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Texture.h"
#include "Types.h"
#include "VoxelGen.h"
#include "OCLNoise.h"


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
	
	m_mouseRotX = 0;
	m_mouseRotY = 0;
	m_mouseLastX = 0;
	m_mouseLastY = 0;
	m_scale = 1.0;
	
	int d = 128;
	int index = 0;
	unsigned char* noisedata = new unsigned char[d*d*d];
	
	OCLNoise* noise = new OCLNoise();
	if(!noise->noise3D(FBM, d, noisedata))
	{
		fprintf(stderr, "Error: Noise generation borked\n");
		exit(EXIT_FAILURE);
	}
	
	VoxelGen* vg = new VoxelGen();
	vg->set3DNoiseData(noisedata, d, 0.01);
	
	m_svr = new SimpleVoxelRenderer();
	m_svr->setVoxelData(vg->voxelData(), vg->voxelCount());
	
	delete[] noisedata;
	delete noise;
	delete vg;
	
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
    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);	
    
    glRotatef(m_mouseRotX, 1, 0, 0);
    glRotatef(m_mouseRotY, 0, 1, 0);
    glScalef(m_scale, m_scale, m_scale);
    
    glTranslatef(-0.5, -0.5, -0.5);
	
	m_svr->draw();
	
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
	gluPerspective(45, m_aspectRatio, 0.05, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLEngine::regenNoise()
{
	
}

