#include "Heightmap.h"

Heightmap::Heightmap(){

}

Heightmap::Heightmap(int width, int height){
	h_width = width;
	h_height = height;
}

float Heightmap::heightFunction(float x, float z){
	float val = 20*perlin->Get3D(x/200.0,z/200.0,100/200.0);
	
	val = val*val*val;
	val += 10* perlin->Get3D(x/20.0,z/22.0, 200/200.0);
	val += 30* perlin->Get3D(x/400.0,z/400.0, -200/200.0);
	if (val > 30) val = 30 + .1*(val - 30);
	return val;
}

void Heightmap::create(){
	perlin = new Perlin(1, 2, 1, 0);
	
	vertices = new VERT**[h_height];
	
	for(int i = 0; i<h_height; i++){
		vertices[i] = new VERT*[h_width];
	}
	
	unsigned int pos = 0;
	
	for (int i = 0; i<h_height; i++){
		for (int j = 0; j<h_width; j++){
			
			VERT * v;
			v = new VERT;
			vertices[i][j] = v;
			
			v->c.x = i;
			v->c.y = heightFunction(i, j);
			v->c.z = j;
			
			v->xy.s = i/50.0; 
			v->xy.t = v->c.y/50.0;
			
			v->yz.s = v->c.y/50.0;
			v->yz.t = j/50.0;
			
			v->xz.s = i/50.0;
			v->xz.t = j/50.0;
			
			COORD3D a;
			COORD3D b;
			COORD3D c;
			
			COORD3D x;
			COORD3D y;
			COORD3D normal;
			
			a.x = i+1;
			a.y = heightFunction(i+1, j);
			a.z = j;
			
			b.x = i;
			b.y = heightFunction(i, j+1);
			b.z = j+1;
			
			c.x = i;
			c.y = heightFunction(i, j-1);
			c.z = j-1;
			
			x.x = a.x - c.x;
			x.y = a.y - c.y;
			x.z = a.z - c.z;
			
			y.x = a.x - b.x;
			y.y = a.y - b.y;
			y.z = a.z - b.z;
			
			normal.x = x.y*x.z - y.y*y.z;
			normal.y = x.x*y.z - y.x*x.z;
			normal.z = x.x*y.y - y.x*x.y;
			
			v->n.x = normal.x;
			v->n.y = normal.y;
			v->n.z = normal.z;
			
			v->pos = pos;
			pos++;
			
		}
	}
	
	triangles = new TRIANGLE*[h_height * h_width * 4];
	t_num = 0;
	for (int i = 0; i<h_height; i++){
		for (int j = 0; j<h_width; j++){
			if ((i+1)<h_height){
				if ((j+1)<h_width){
					//
					//  a---b
					//  |\  |
					//  | \ |  
					//  |  \|
					//  c---d
					
					VERT * a = vertices[i][j];
					VERT * b = vertices[i][j+1];
					VERT * c = vertices[i+1][j];
					VERT * d = vertices[i+1][j+1];
					
					TRIANGLE * t = NULL;
					t = new TRIANGLE;

					triangles[t_num] = t;

					
					
					t->a = a;
					t->b = d;
					t->c = b;
					
					t_num ++;
				
					TRIANGLE * t2 = NULL;
					t2 = new TRIANGLE;
				
					triangles[t_num] = t2;
					
					t2->a = a;
					t2->b = c;
					t2->c = d;
					
					
					t_num ++;
				}
			}
			
		}
	} 
	
}

void Heightmap::draw(){
	
	TRIANGLE * t;
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i<t_num; i++){
		t = triangles[i];
		glVertex3f(t->a->c.x, t->a->c.y, t->a->c.z);
		glVertex3f(t->b->c.x, t->b->c.y, t->b->c.z);
		glVertex3f(t->c->c.x, t->c->c.y, t->c->c.z);
	}
	glEnd();

}

void Heightmap::setShader(unsigned int program){
	shader = program;
}

void Heightmap::writeToImage(){

	sf::Color col(0,0,0,255);
	sf::Image img(h_width, h_height, NULL);
	for (int i = 0; i<h_height; i++){
		for (int j = 0; j<h_width; j++){
			VERT * v = vertices[i][j];
			Uint8 val = (Uint8)(((v->c.y)+.5)*255.0);
			col.r = val;
			col.g = val;
			col.b = val;
			col.a = 255;
			img.SetPixel(i,j,col);
		}
	}
	img.SaveToFile((char*)"heightmap.png");

}

MeshObject * Heightmap::convertToMesh(){
	
	MeshObject * mo = new MeshObject;
	TRIANGLE * t;
	VERT * a;
	VERT * b;
	VERT * c;
	
	float * verts = new float[h_height * h_width * 3];
	int v_count = 0;
	float * yzcoords = new float[h_height * h_width *2];
	int yzcount = 0;
	float * xzcoords = new float[h_height * h_width *2];
	int xzcount = 0;
	float * xycoords = new float[h_height * h_width *2];
	int xycount = 0;
	float * norms = new float[h_height * h_width * 3];
	int n_count = 0;
	unsigned short * vorder = new unsigned short[t_num*3];
	int i_count = 0;
	
	/// DEAL WITH NORMALS AND VERTICES
	
	for (int i = 0; i < h_height; i++){
		for (int j = 0; j < h_width; j++){
			a = vertices[i][j];
			
			verts[v_count] = a->c.x;
			v_count++;
			verts[v_count] = a->c.y;
			v_count++;
			verts[v_count] = a->c.z;
			v_count++;
			
			yzcoords[yzcount] = a->yz.s;
			yzcount++;
			yzcoords[yzcount] = a->yz.t;
			yzcount++;
			
			xzcoords[xzcount] = a->xz.s;
			xzcount++;
			xzcoords[xzcount] = a->xz.t;
			xzcount++;
			
			xycoords[xycount] = a->xy.s;
			xycount++;
			xycoords[xycount] = a->xy.t;
			xycount++;
			norms[n_count] = a->n.x;
			n_count++;
			norms[n_count] = a->n.y;
			n_count++;
			norms[n_count] = a->n.z;
			n_count++;
		}
	}
	
	// DEAL WITH INDICES
	
	for (int i = 0; i < t_num; i++){
		t = triangles[i];
		a = t->a;
		b = t->b;
		c = t->c;
		
		vorder[i_count] = a->pos;
		i_count++;
		vorder[i_count] = b->pos;
		i_count++;
		vorder[i_count] = c->pos;
		i_count++;	
		
	}
	
	vbo_data * vData = new vbo_data;
	vData->verts = verts;
	vData->yztex = yzcoords;
	vData->xztex = xzcoords;
	vData->xztex = xzcoords;
	vData->norms = norms;
	vData->v_count = v_count;
	
	vData->vorder = vorder;
	
	vData->i_count = i_count;
	mo->c_shader = shader;
	mo->set(vData);
	return mo;
}
