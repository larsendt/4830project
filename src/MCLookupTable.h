#ifndef MC_LOOKUP_TABLE_H
#define MC_LOOKUP_TABLE_H

// the marching cubes lookup table

float MCVertices[12][3] = {
	{0.5, 0.0, 0.0}, // edge between 0 and 1 - 1
	{0.0, 0.5, 0.0}, // edge between 0 and 2 - 2
	{0.0, 0.0, 0.5}, // edge between 0 and 3 - 3
	{1.0, 0.5, 0.0}, // edge between 1 and 4 - 4
	{1.0, 0.0, 0.5}, // edge between 1 and 6 - 5
	{0.5, 1.0, 0.0}, // edge between 2 and 4 - 6
	{0.0, 1.0, 0.5}, // edge between 2 and 5 - 7
	{0.0, 0.5, 1.0}, // edge between 3 and 5 - 8
	{0.5, 0.0, 1.0}, // edge between 3 and 6 - 9 
	{1.0, 1.0, 0.5}, // edge between 4 and 7 - 10
	{0.5, 1.0, 1.0}, // edge between 5 and 7 - 11
	{1.0, 0.5, 1.0}  // edge between 6 and 7 - 12
};


// layout is GL_TRIANGLES
// first index is number of vertices
// encoded as c strings, so last number must be zero
// indices are 1-indexed, so subtract one when getting the appropriate vertex (since zero is used to terminate)
char MCIndices[256][13] = {
	{ 0}, // no vertices set
	{ 3,  2,  1,  0}, // vx 0 is set
	{ 5,  4,  1,  0}, // 1
	{ 7,  6,  2,  0}, // 2
	{ 9,  8,  3,  0}, // 3
	{10,  6,  4,  0}, // 4
	{11,  8,  7,  0}, // 5
	{12,  9,  5,  0}, // 6
	{12, 11, 10,  0}, // 7
	{2,  4,  3,  5,  3,  4,  0}, // 0 1
	{1,  3,  7,  7,  6,  1,  0}, // 0 2
	{1,  2,  8,  8,  9,  1,  0}, // 0 3
	{0,  6, 10, 10,  5,  0,  0}, // 1 4
	{1,  4, 12, 12,  9,  1,  0}, // 1 6
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
	{ 3,  2,  1,  0}, // placeholder
};

float* MCGetVertex(int vertex_id)
{
	return MCVertices[vertex_id-1];
}

#endif
