#pragma once

// change this to 1 to use the OpenCL implementation
#define OPENCL 0

#define meter 1
#define kilometer 1000
#define CHUNK_SIZE 128
#define WORLD_MIN 0
#define WORLD_MAX 2

/*
	All complex types that cross class boundaries are defined here
*/

struct COORD3D {
	float x;
	float y;
	float z;
};

struct COORD2D {
	float s;
	float t;
};

struct COLOR {
	float r;
	float g;
	float b;
	float a;
};

struct VERTEX{
	COORD3D c;
	COORD3D n;
	COORD2D xy;
	COORD2D xz;
	COORD2D yz;
	float padding[4]; // 32 byte alignment to make everything easier
};



struct VOXEL {
	COORD3D pos;
};

struct TRIANGLE{
	VERTEX * a;
	VERTEX * b;
	VERTEX * c;
};
