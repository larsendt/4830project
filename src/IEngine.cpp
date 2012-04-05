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
	Shader * fbo_shader = new Shader((char*)"shaders/pp.vert",(char*)"shaders/heat.frag");
	p.setShader(fbo_shader);
	p.init(m_window->GetWidth(), m_window->GetHeight());
	
	
	unsigned int tex2 = loadImage((char*)"tex/forest.jpg");
	unsigned int tex = loadImage((char*)"tex/lavarock.jpg");
	
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
	mo = new MeshObject();
	mc = new SoftwareMarchingCubes();
	int m_dim = 128;
	mo->setShader(sh->getID());
	genNoise(m_dim);
	
	m_wireframe = false;
	
	pitch = 0;
	yaw = 0;
	xpos = 50;
	ypos = 10;
	zpos = 50;
	// END TEST
}

void IEngine::initGL(int argc, char** argv)
{
	m_window = new sf::Window(sf::VideoMode(800, 600, 32), "IEngine");
	m_clock = new sf::Clock();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPointSize(5.0);
	glEnable(GL_POINT_SMOOTH);
	glLineWidth(2.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
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
		yaw ++;
	}
	if (d){
		yaw --;
	}
	if (w){
		pitch++;
	}
	if (s){
		pitch--;
	}
	
	if (up){
		float z = -(cos(mradians(yaw)));
		float y = (sin(mradians(pitch)));
		float x = -(sin(mradians(yaw)));
		xpos += x;
		ypos += y;
		zpos += z;
	}
	
	if (down){
		float z = (cos(mradians(yaw)));
		float y = -(sin(mradians(pitch)));
		float x = (sin(mradians(yaw)));
		xpos += x;
		ypos += y;
		zpos += z;
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
	p.startDraw();
	if (m_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glRotatef(-pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);
	glTranslatef(-xpos, -ypos, -zpos);

	mo->draw();
	glColor3f(0.0,0.0,1.0);
	
	glBegin(GL_LINES);
	glVertex3f(-1000.0,0.0,0.0);
	glVertex3f(1000.0,0.0,0.0);
	glVertex3f(0.0,-1000.0,0.0);
	glVertex3f(0.0, 1000.0,0.0);
	glVertex3f(0.0,0.0,-1000.0);
	glVertex3f(0.0,0.0,1000.0);
	glEnd();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	p.draw();
	
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

void IEngine::genNoise(int dim)
{
	printf("Generating terrain with size %d (%dx%dx%d)\n", dim*dim*dim, dim, dim, dim);
	
	int d = dim;
	float s = 100.0/d;
	int index = 0;
	unsigned char* noisedata = new unsigned char[d*d*d];
	
	OCL3DFBMNoise* noise = new OCL3DFBMNoise();
	if(!noise->noise(d, noisedata))
	{
		fprintf(stderr, "Error: Noise generation borked\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Marching cubes generating mesh...\n");
	mc->setNoiseData(noisedata, d, s);
	mc->runOutToMesh(mo);
	printf("Done\n");
		
	delete[] noisedata;
	delete noise;
}
