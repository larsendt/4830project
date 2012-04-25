//////////////////////////////////////////
///           IEngine.cpp
//////////////////////////////////////////

#include "IEngine.h"

IEngine::IEngine(int argc, char** argv)
{
	printf("Initializing IEngine\n");
	initGL(argc, argv);
	resize(800, 600);
	m_time = 0.0;
	frames = 0;
	m_updateRate = 0.01;
	
	// TEST STUFF
	
	water = new Water();
	
	Shader * watershader = new Shader((char*)"shaders/water.vert",(char*)"shaders/water.frag");
	
	water->setShader(watershader->getID());
	water->init(m_window->GetWidth(), m_window->GetHeight());
	
	Shader * fbo_shader = new Shader((char*)"shaders/pp.vert",(char*)"shaders/depthdet.frag");
	p.setShader(fbo_shader);
	p.init(m_window->GetWidth(), m_window->GetHeight());
	
	unsigned int tex2 = loadImage((char*)"tex/grass.png");
	unsigned int tex = loadImage((char*)"tex/sand.jpg");
	sh2 = new Shader((char *) "shaders/watertriplanar.vert", (char*)"shaders/watertriplanar.frag");
	sh = new Shader((char*)"shaders/triplanar.vert", (char*)"shaders/triplanar.frag");
	
	sh->bind();
	
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	bindImage(tex);
	
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE3);
	bindImage(tex2);
	
	sh->setUniform1i((char*)"tex", 2);
	sh->setUniform1i((char*)"tex2", 3);
	
	w.m_gen.shader = sh->getID();
	m_wireframe = false;
	
	pitch = 0;
	yaw = -90;
	c_pos.x = -32; c_pos.y = 10; c_pos.z = 96;
	c_speed.x = 0; c_speed.y = 0; c_speed.z = 0;
	
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
	
	
	/*water->bindReflection();
	
	vec3 ref_pos = water->getReflectionPosition(c_pos, ref_pitch);
	glPushMatrix();
	glRotatef(-ref_pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);
	glTranslatef(-ref_pos.x, -ref_pos.y, -ref_pos.z);
	w.drawAt(0,0,0);
	glPopMatrix();
	water->unbindReflection();*/
	
	//p.startDraw();
	
	if (m_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	float ref_pitch = pitch;
	vec3 ref_pos = water->getReflectionPosition(c_pos, ref_pitch);
	
	glPushMatrix();
	glLoadIdentity();
	
	glScalef(1,1,1);
	glRotatef(-pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);
	glTranslatef(-c_pos.x, -c_pos.y, -c_pos.z);
	//water->protectDepthBuffer();
	//water->stencilBuffer(c_pos, pitch, yaw);
	
	glUseProgram(sh2->getID());
	w.drawAt(0,0,0);
	
	glPopMatrix();
	
	glPushMatrix();
	glLoadIdentity();
	
	glRotatef(-pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);

	glTranslatef(-c_pos.x, -c_pos.y, -c_pos.z);

	glUseProgram(sh->getID());
	w.drawAt(0,0,0);

	glPopMatrix();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//p.draw();
	
	
}


void IEngine::update()
{
	time += m_clock->GetElapsedTime();
	float multiplier = 1.0;
	while(m_clock->GetElapsedTime() < m_updateRate)
    	continue;
    	
   	if(time > m_updateRate)
	{
		multiplier = time / m_updateRate;
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
	gluPerspective(45.0,m_width,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	p.resize(width, height);
}
