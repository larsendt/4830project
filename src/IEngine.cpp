//////////////////////////////////////////
///           IEngine.cpp
//////////////////////////////////////////

#include "IEngine.h"

#include <unistd.h>
#include <time.h>

IEngine::IEngine(int argc, char** argv)
{
	printf("Initializing IEngine\n");
	initGL(argc, argv);
	resize(800, 600);
	m_time = 0.0;
	frames = 0;
	m_updateRate = 0.01;
	
	if(argc == 2)
	{
		m_seed = atoi(argv[1]);
	}
	else
	{
		srand(time(NULL));
		m_seed = 817901691;//rand();
	}
	
	printf("Using seed: %d\n", m_seed);
	// TEST STUFF
	
	water = new Water();
	
	Shader * watershader = new Shader((char*)"shaders/water.vert",(char*)"shaders/water.frag");
	
	water->setShader(watershader->getID());
	water->init(m_window->GetWidth(), m_window->GetHeight());
	
	Shader * fbo_shader = new Shader((char*)"shaders/pp.vert",(char*)"shaders/depthdet.frag");
	p.setShader(fbo_shader);
	p.init(m_window->GetWidth(), m_window->GetHeight());
	
	tex3 = loadImage((char*)"tex/rock.jpg");
	tex2 = loadImage((char*)"tex/grass.png");
	tex = loadImage((char*)"tex/sand.jpg");
	sh2 = new Shader((char *) "shaders/watertriplanar.vert", (char*)"shaders/watertriplanar.frag");
	sh = new Shader((char*)"shaders/triplanar.vert", (char*)"shaders/triplanar.frag");
	waterShader = new Shader((char*)"shaders/waterripple.vert", (char*)"shaders/waterripple.frag");
	
	sh->bind();
	
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	bindImage(tex);
	
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE3);
	bindImage(tex2);
	
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE4);
	bindImage(tex3);
	
	sh->setUniform1i((char*)"tex", 2);
	sh->setUniform1i((char*)"tex2", 3);
	sh->setUniform1i((char*)"tex3", 4);
	
	
	w.m_gen.shader = sh->getID();
	w.setSeed(m_seed);
	m_wireframe = false;
	
	pitch = 0;
	yaw = -90;
	c_pos.x = 30; c_pos.y = 32; c_pos.z = 80;
	c_speed.x = 0; c_speed.y = 0; c_speed.z = 0;
	
	skybox = new Skybox();
	
	// END TEST
}

void IEngine::initGL(int argc, char** argv)
{
	m_window = new sf::Window(sf::VideoMode(800, 600, 32), "IEngine");
	m_clock = new sf::Clock();
	glClearColor(.6,.6,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPointSize(5.0);
	glEnable(GL_POINT_SMOOTH);
	glLineWidth(4.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
}

void IEngine::checkKeys(){

	// This function deals with constant keypresses.
	
	const sf::Input& input = m_window->GetInput();
	bool a = input.IsKeyDown(sf::Key::A);
	bool d = input.IsKeyDown(sf::Key::D);
	bool w = input.IsKeyDown(sf::Key::W);
	bool s = input.IsKeyDown(sf::Key::S);
	
	bool up = input.IsKeyDown(sf::Key::Up);
	bool down = input.IsKeyDown(sf::Key::Down);
	
	if (a){
		yaw += .6;
	}
	if (d){
		yaw -= .6;
	}
	if (w){
		pitch += .6;
	}
	if (s){
		pitch -= .6;
	}
	
	if (up){
		float z = -(cos(mradians(yaw)))*(cos(mradians(pitch)));
		float y = (sin(mradians(pitch)));
		float x = -(sin(mradians(yaw)))*(cos(mradians(pitch)));
		c_speed.x += .002*x;
		c_speed.y += .002*y;
		c_speed.z += .002*z;
	}
	else if (down){
		float z = (cos(mradians(yaw)))*cos(mradians(pitch));
		float y = -(sin(mradians(pitch)));
		float x = (sin(mradians(yaw)))*cos(mradians(pitch));
		c_speed.x += .002*x;
		c_speed.y += .002*y;
		c_speed.z += .002*z;
	}
	else
	{
		float len;
		if ((len = c_speed.length()) > .01){
			c_speed = c_speed.normalize() * (len-.01);
		}
		else c_speed = vec3(0,0,0);
	}
	
}

int IEngine::begin()
{

	while(m_window->IsOpened())
	{
		sf::Event Event;
		checkKeys();
		while(m_window->GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
			{
				m_window->Close();
				return 0;
			}
			
			else if(Event.Type == sf::Event::KeyPressed)
			{
				// For one-press keys: (starts to repeat after a while)
				if(Event.Key.Code == sf::Key::Escape)
				{
					m_window->Close();
					return 0;
				}
				if(Event.Key.Code == sf::Key::M)
				{
					m_wireframe = true;
				}
				if(Event.Key.Code == sf::Key::N)
				{
					m_wireframe = false;
				}
				if(Event.Key.Code == sf::Key::R){
					c_pos = vec3(0,CHUNK_SIZE,0);
					c_speed = vec3(0,0,0);
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


void IEngine::drawScene()
{
	
	p.startDraw();
	
	if (m_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	
	glActiveTexture(GL_TEXTURE2);
	bindImage(0);

	glActiveTexture(GL_TEXTURE3);
	bindImage(0);
	
	glActiveTexture(GL_TEXTURE4);
	bindImage(0);

	glTranslatef(0, -c_pos.y, 0);

	//glTranslatef(0, -25, 0);	
	glRotatef(-pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);
	skybox->draw();
	
	glPopMatrix();

	
	float ref_pitch = pitch;
	vec3 ref_pos = water->getReflectionPosition(c_pos, ref_pitch);
	
	int drawx, drawz;
	drawx = (int) (c_pos.x / CHUNK_SIZE);
	drawz = (int) (c_pos.z / CHUNK_SIZE);
	
	//////////////////////////////////////
	/// Draw the inverted terrain
	//////////////////////////////////////
	
	if(c_pos.y > 0.0){
	
		glPushMatrix();
		glLoadIdentity();
	
		glRotatef(-pitch, 1,0,0);
		glRotatef(-yaw, 0,1,0);
		glTranslatef(-c_pos.x, -c_pos.y, -c_pos.z);
		//water->protectDepthBuffer();
		//water->stencilBuffer(c_pos, pitch, yaw);
		
		sh2->bind();
		
		glActiveTexture(GL_TEXTURE2);
		bindImage(tex);
	
		glActiveTexture(GL_TEXTURE3);
		bindImage(tex2);
	
		glActiveTexture(GL_TEXTURE4);
		bindImage(tex3);
	
		sh2->setUniform1i((char*)"tex", 2);
		sh2->setUniform1i((char*)"tex2", 3);
		sh2->setUniform1i((char*)"tex3", 4);
		
		sh2->setUniform1f("time", frames * .1);
		w.drawAt(drawx,0,drawz);
		sh2->release();
	
	}
	
	//////////////////////////////////////////
	/// Draw the water polygon
	//////////////////////////////////////////
	
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLES);
	static int inc = 20;
	glColor4f(0.0,.05,.1,.6);
	for(int i = -1000; i < 1000; i+=inc){
		for(int j = -1000; j < 1000; j+=inc){
			glVertex3f(i, 0, j);
			glVertex3f(i+inc, 0, j);
			glVertex3f(i+inc, 0, j+inc);
			glVertex3f(i, 0, j);
			glVertex3f(i, 0, j+inc);
			glVertex3f(i+inc, 0, j+inc);
		}
	}
	glEnd();
	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	glPopMatrix();
	
		
	//////////////////////////////////////
	///  Draw the primary terrain
	//////////////////////////////////////
	glPushMatrix();
	glLoadIdentity();
	
	glRotatef(-pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);

	glTranslatef(-c_pos.x, -c_pos.y, -c_pos.z);

	sh->bind();
	
	glActiveTexture(GL_TEXTURE2);
	bindImage(tex);
	
	glActiveTexture(GL_TEXTURE3);
	bindImage(tex2);
	
	glActiveTexture(GL_TEXTURE4);
	bindImage(tex3);
	
	sh->setUniform1i((char*)"tex", 2);
	sh->setUniform1i((char*)"tex2", 3);
	sh->setUniform1i((char*)"tex3", 4);
	
	w.drawAt(drawx,0,drawz);
	glPopMatrix();

	sh->release();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	p.draw();
	
	
}


void IEngine::update()
{
	m_time += m_clock->GetElapsedTime();
	float multiplier = 1.0;
	frames ++;
	while(m_clock->GetElapsedTime() < m_updateRate)
    	continue;
    	
   	if(m_time > m_updateRate)
	{
		multiplier = m_time / m_updateRate;
	}
	
	c_pos = c_pos + c_speed;
	if (fabs(yawspeed) < .01){
		yawspeed = 0;
	}
	else yawspeed = (fabs(yawspeed)-.01)*(yawspeed<0?-1:1);
	yaw = yaw + yawspeed;
	if (fabs(pitchspeed) < .01){
		pitchspeed = 0;
	}
	else pitchspeed = (fabs(pitchspeed)-.01)*(pitchspeed<0?-1:1);
	pitch = pitch + pitchspeed;
	
    m_clock->Reset();

}


void IEngine::resize(int width, int height)
{

	m_width = (height>0) ? (GLfloat)width/height : 1;
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,m_width,1,500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	p.resize(width, height);
}
