#ifndef TYPES_H
#define TYPES_H

/*
	All complex types that cross class boundaries are defined here
*/

struct COORD3D {
	float a;
	float b;
	float c;
};

struct NORMAL {
	float a;
	float b;
	float c;
};

struct VERTEX {
	COORD3D * pos;
	NORMAL * norm;
};

struct TEXCOORD2D {
	float s;
	float t;
};

struct EDGE {
	VERTEX* a;
	VERTEX* b;
};

struct TRIANGLE {
	EDGE * ab;
	EDGE * bc;
	EDGE * ca;
	
};

struct VOXEL {
	COORD3D* pos;
};

#endif
