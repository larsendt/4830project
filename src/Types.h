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

struct COLOR {
	float r;
	float g;
	float b;
	float a;
};

struct NORMAL {
	float a;
	float b;
	float c;
};

struct VERTEX {
	COORD3D pos;
	NORMAL norm;
	COLOR color;
};

struct TEXCOORD2D {
	float s;
	float t;
};

struct VOXEL {
	COORD3D pos;
};

#endif
