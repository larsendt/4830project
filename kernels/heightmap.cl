/* vertex layout

00 01 02 03 04
05 06 07 08 09
10 11 12 13 14
15 16 17 18 19
20 21 22 23 24

first triangle would be
01 06 02 (index, width+index, index+1)

second would be 
02 06 07 (index+1, width+index, index)

*/


__kernel void generate_heightmap(__global uchar4* bitmap, __global float* vertices, __global float* normals, __global int* indices, int dim, float spacing)
{
	int bitmap_index = (get_global_id(1) * dim) + get_global_id(0); // index into the input bitmap
	int vertex_index = (get_global_id(0) * dim) + get_global_id(1);
	float height = bitmap[bitmap_index].x / 255.0; // produces output between 0 and 1
	
	indices[vertex_index] = get_global_id(0);
}
