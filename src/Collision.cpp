#include "Collision.h"

float SquaredLength(glm::vec3 v){

	return (v.x*v.x + v.y*v.y + v.z*v.z);

}
float SignedDistance(glm::vec3 N, glm::vec3 p, glm::vec3 O){

	return (glm::dot(N,p)+(-(N.x*O.x+N.y*O.y+N.z*O.z)));

}

glm::vec3 normal(glm::vec3 a, glm::vec3 b, glm::vec3 c){

	glm::vec3 n;
	glm::vec3 u = b-a;
	glm::vec3 v = c-a;
	n.x = (u.y*v.z - u.z*v.y);
	n.y = (u.z*v.x - u.x*v.z);
	n.z = (u.x*v.y - u.y*v.x);
	return -glm::normalize(n);

}

int checkCollide(glm::vec3 N,glm::vec3 p,glm::vec3 vel, glm::vec3 ta, glm::vec3 tb, glm::vec3 tc, glm::vec3 &result, float &distance){

	// Figure out two times, t0 and t1. 
	// By finding the signed distance to the plane at two places.
	// We want to know if a) it intersects the plane of the triangle
	// b) if it is within the bounds of the triangle (ta/tb/tc)
	// c) or if it's on the edges / points of the triangles. 
	// This function returns 1 if it does intersect, or 0 otherwise. 
	// get interval of intersection
	
	float t0, t1;
	bool embedded = false;
	
	// calc distance
	
	float distToPlane = SignedDistance(N,p,ta);
	
	float nDvel = glm::dot(N,vel);
	
	if (nDvel < 0.0f){
		if (fabs(distToPlane) >= 1.0f){
			return 0;
		}
	
		else {
		embedded = true;
		t0 = 0.0;
		t1 = 1.0;
		}
	}
	else{
		t0 = (-1.0-distToPlane)/nDvel;
		t1 = (1.0 - distToPlane)/nDvel;
		
		if (t0 > t1){
			float temp = t1;
			t1 = t0;
			t0 = temp;
		}
		
		if (t0>1.0f || t1< 0.0f){
			return 0;
		}
		
		if (t0<0.0) t0 = 0.0;
		if (t1<0.0) t1 = 0.0;
		if (t0>1.0) t0 = 1.0;
		if (t1>1.0) t1 = 1.0;
	}
	
	glm::vec3 colPoint;
	bool foundCol = false;
	float t = 1.0;
	glm::vec3 planeIntersect = (p-N + t0*vel);
	if (!embedded){
		
		
		if(checkPointInTriangle(planeIntersect, ta, tb, tc)){
			foundCol = true;
			t = t0;
			colPoint = planeIntersect;
			distance = t*glm::length(vel);
			result = colPoint;
			return 1;
		}
		return 0;
	}
	
	/// VERY IMPORTANT. This is where it checks for intersection in the area of the triangle.
	else {
		if(checkPointInTriangle(planeIntersect, ta, tb, tc)){
			foundCol = true;
			t = t0;
			colPoint = planeIntersect;
			distance = t*glm::length(vel);
			result = colPoint;
			return 1;
		}
	
	}
	if (foundCol ==false){
		glm::vec3 base = p;
		float velSquared = SquaredLength(vel);
		float a,b,c;
		float newT;
		
		a = velSquared;
		
		// for ta
		b = 2.0f*glm::dot(vel,base-ta);
		c = SquaredLength(ta - base) -1.0;
		if (getLowestRoot(a,b,c,t, &newT)){
			t = newT;
			foundCol = true;
			colPoint = ta;
			distance = t*glm::length(vel);
			result = colPoint;
			return 1;
		}
		
		// for tb
		b = 2.0f*glm::dot(vel,base-tb);
		c = SquaredLength(tb - base) -1.0;
		if (getLowestRoot(a,b,c,t, &newT)){
			t = newT;
			foundCol = true;
			colPoint = tb;
			distance = t*glm::length(vel);
			result = colPoint;
			return 1;
		}
		
		// for tc
		b = 2.0f*glm::dot(vel,base-tc);
		c = SquaredLength((tc - base)) -1.0;
		if (getLowestRoot(a,b,c,t, &newT)){
			t = newT;
			foundCol = true;
			colPoint = tc;
			distance = t*glm::length(vel);
			result = colPoint;
			return 1;
		}
		
		// now edges
		
		// ta -> tb
		glm::vec3 edge = tb-ta;
		glm::vec3 baseToVertex = ta - base;
		float edgeSquared = SquaredLength(edge);
		float edgeDotVel = glm::dot(edge, vel);
		float edgeDotBaseToVert = glm::dot(edge, baseToVertex);
		
		a = edgeSquared*-velSquared + edgeDotVel*edgeDotVel;
		b = edgeSquared*(2*glm::dot(vel,baseToVertex))-2.0*edgeDotVel*edgeDotBaseToVert;
		c = edgeSquared*(1-SquaredLength(baseToVertex))+edgeDotBaseToVert*edgeDotBaseToVert;
		
		if (getLowestRoot(a,b,c,t,&newT)){
			float f = (edgeDotVel*newT - edgeDotBaseToVert)/edgeSquared;
			if(f>=0.0 && f<=1.0){
				t = newT;
				foundCol = true;
				colPoint = ta + f*edge;
				distance = t*glm::length(vel);
				result = colPoint;
				return 1;
			}
		}
		
		// tb -> tc
		edge = tc-tb;
		baseToVertex = tb - base;
		edgeSquared = SquaredLength(edge);
		edgeDotVel = glm::dot(edge, vel);
		edgeDotBaseToVert = glm::dot(edge,baseToVertex);
		
		a = edgeSquared*-velSquared + edgeDotVel*edgeDotVel;
		b = edgeSquared*(2*glm::dot(vel,baseToVertex))-2.0*edgeDotVel*edgeDotBaseToVert;
		c = edgeSquared*(1-SquaredLength(baseToVertex))+edgeDotBaseToVert*edgeDotBaseToVert;
		
		if (getLowestRoot(a,b,c,t,&newT)){
			float f = (edgeDotVel*newT - edgeDotBaseToVert)/edgeSquared;
			if(f>=0.0 && f<=1.0){
				t = newT;
				foundCol = true;
				colPoint =tb + f*edge;
				distance = t*glm::length(vel);
				result = colPoint;
				return 1;
			}
		}
		
		// tc -> ta
		edge = ta-tc;
		baseToVertex = tc - base;
		edgeSquared = SquaredLength(edge);
		edgeDotVel = glm::dot(edge, vel);
		edgeDotBaseToVert = glm::dot(edge,baseToVertex);
		
		a = edgeSquared*-velSquared + edgeDotVel*edgeDotVel;
		b = edgeSquared*(2*glm::dot(vel,baseToVertex))-2.0*edgeDotVel*edgeDotBaseToVert;
		c = edgeSquared*(1-SquaredLength(baseToVertex))+edgeDotBaseToVert*edgeDotBaseToVert;
		
		if (getLowestRoot(a,b,c,t,&newT)){
			float f = (edgeDotVel*newT - edgeDotBaseToVert)/edgeSquared;
			if(f>=0.0 && f<=1.0){
				t = newT;
				foundCol = true;
				colPoint =tc + f*edge;
				distance = t*glm::length(vel);
				result = colPoint;
				return 1;
			}
		}
	}
	distance = t*glm::length(vel);
	return 0;

}

// Thanks to a Keidy from Mr-Gamemaker for this algorithm. 

typedef unsigned int uint32;
#define in(a) ((uint32&) a)
bool checkPointInTriangle(glm::vec3 point, 
							glm::vec3 pa,
							glm::vec3 pb, 
							glm::vec3 pc){
	glm::vec3 e10=pb-pa;
	glm::vec3 e20=pc-pa;
	float a = glm::dot(e10,e10);
	float b = glm::dot(e10,e20);
	float c = glm::dot(e20,e20);
	float ac_bb=(a*c)-(b*b);
	glm::vec3 vp = point-pa;
	
	float d = glm::dot(vp,e10);
	float e = glm::dot(vp,e20);
	float x = (d*c)-(e*b);
	float y = (e*a)-(d*b);
	float z = x+y-ac_bb;
	
	return (( in(z)&~(in(x)|in(y)))&0x80000000);
}

bool getLowestRoot(float a, float b, float c, float maxR, float* root){
	float det = b*b - 4.0f*a*c;
	
	if (det < 0.0f) return false;
	
	float detroot = sqrt(det);
	float r1 = (-b - detroot) / (2*a);
	float r2 = (-b + detroot) / (2*a);
	
	if (r1>r2){
		float temp = r2;
		r2 = r1;
		r1 = temp;
		
	}
	
	if (r1>0 && r1 < maxR){
		*root = r1;
		return true;
	}
	
	
	if (r2>0 && r2<maxR){
		*root = r2;
		return true;
	}
	
	return false;
}

GLint circle(){

	int name;
	name = glGenLists(1);
	glNewList(name, GL_COMPILE);
	
	int inc = 10;
	double x,y,z;
	double tx, ty, tx1, ty1;
	for (int ph = -90; ph<90;ph+=inc){
		glBegin(GL_QUAD_STRIP);
		//glVertex3f(sin((i)*3.14/180)/3, 0, cos((i)*3.14/180)/3);
		for(int th = 0; th<=360; th+=(2*inc)){
			float xoffset = (rand()%100)/500.0;
			float yoffset = (rand()%100)/500.0;
			float zoffset = (rand()%100)/500.0;
			x = sin(th * PI/180)*cos(ph * PI/180);
			y = cos(th * PI/180)*cos(ph * PI/180);
			z = sin(ph * PI/180);
			
			glNormal3f(x,y,z);
			glVertex3f(x,y,z);
			
			xoffset = (rand()%100)/500.0;
			yoffset = (rand()%100)/500.0;
			zoffset = (rand()%100)/500.0;
			
			x = sin(th * PI/180)*cos((ph+inc) * PI/180);
			y = cos(th * PI/180)*cos((ph+inc) * PI/180);
			z = sin((ph+inc) * PI/180);
			
			glNormal3f(x,y,z);
			glVertex3f(x,y,z);
			
		}
		glEnd();
		

	}
	glEndList();
	return name;
}
