#include "Polygonize.h"

#include "MCLookupTable.h"

MeshObject * convertToMesh(MeshObject * mesh, VoxelCube voxels, int dim, float spacing, unsigned char isolevel){

	COORD3D cube[8];
	int index = 0;
	cube[index].x = 0; cube[index].y = 0; cube[index].z = 0;
	index = 1;
	cube[index].x = 1; cube[index].y = 0; cube[index].z = 0;
	index = 2;
	cube[index].x = 1; cube[index].y = 0; cube[index].z = 1;
	index = 3;
	cube[index].x = 0; cube[index].y = 0; cube[index].z = 1;
	index = 4;
	cube[index].x = 0; cube[index].y = 1; cube[index].z = 0;
	index = 5;
	cube[index].x = 1; cube[index].y = 1; cube[index].z = 0;
	index = 6;
	cube[index].x = 1; cube[index].y = 1; cube[index].z = 1;
	index = 7;
	cube[index].x = 0; cube[index].y = 1; cube[index].z = 1;
	
	// we start with 512 vertices and allocate more if necessary
	int max_vxs = 512;
	VERTEX* vertices = (VERTEX*) malloc(max_vxs * sizeof(*vertices));
	GLuint* indices = (GLuint*) malloc(max_vxs * sizeof(*indices)); 
	int vx_count = 0;
	
	for(int x = 0; x < dim-1; x++)
	{
		for(int y = 0; y < dim-1; y++)
		{
			for(int z = 0; z < dim-1; z++)
			{
				unsigned char noisevals[8];
				unsigned int indices1d[8];
				unsigned int cubeindex = 0;
				
				for(int i = 0; i < 8; i++)
				{
					noisevals[i] = voxels.at(x+cube[i].x, y+cube[i].y, z+cube[i].z); 
					if(noisevals[i] < isolevel) cubeindex |= (unsigned char)pow(2, i);
				}
			
				if(cubeindex != 0xff && cubeindex != 0x0)
				{
					unsigned char* ids = indexTable[cubeindex];
					int idcount = indexCountTable[cubeindex];
					COORD3D cachedCoords[16];
					int tmpcount = vx_count;
					
					for(int i = 0; i < idcount; i++)
					{
						COORD3D c;
						
						int edge0 = edgeMap[ids[i]][0];
						int edge1 = edgeMap[ids[i]][1];
						COORD3D temp = vInterpolation(isolevel, cube[edge0], cube[edge1], noisevals[edge0], noisevals[edge1]);
						
						c.x = (x*spacing) + (temp.x*spacing);
						c.y = (y*spacing) + (temp.y*spacing);
						c.z = (z*spacing) + (temp.z*spacing);
						
						cachedCoords[i] = c;
						
						COORD2D xy;
						
						xy.s = (float)c.x/(float)dim;
						xy.t = (float)c.y/(float)dim;
						
						COORD2D xz;
						
						xz.s = (float)c.x/(float)dim;
						xz.t = (float)c.z/(float)dim;
						
						COORD2D yz;
						
						yz.s = (float)c.y/(float)dim;
						yz.t = (float)c.z/(float)dim;
						
						COLOR color;
						
						color.r = c.x;
						color.g = c.y;
						color.b = c.z;
						color.a = 1.0;
				
						// allocate more memory if necessary
						if(vx_count == max_vxs)
						{
							max_vxs *= 2;
							vertices = (VERTEX*) realloc(vertices, max_vxs * sizeof(*vertices));
							indices = (GLuint*) realloc(indices, max_vxs * sizeof(*indices));
						}
				
						vertices[vx_count].c = c;
						vertices[vx_count].xy = xy;
						vertices[vx_count].xz = xz;
						vertices[vx_count].yz = yz;
						
						indices[vx_count] = vx_count;
						vx_count ++;
					}
					
					for (int i = 0; i< idcount; i++){
						// n is a placeholder normal indicating the approximate direction the normal should point.
						// The vertex table does not define triangles in a consistent way, so the vector
						// cross product doesn't quite work. This normal should be pointing out of the terrain, 
						// where out is defined as voxels >= 128. If the dot product of this vector and the
						// normal obtained from the cross product is greater than zero, then the cross
						// product is correct. Otherwise, the normal obtained from the cross product should
						// be reversed
						COORD3D n;
					
						vec3 va, vb, vc;
				
						switch (i%3){
							case 0:
								va = vec3(cachedCoords[i].x, 
										cachedCoords[i].y, 
										cachedCoords[i].z);
								vb = vec3(cachedCoords[i+1].x, 
										cachedCoords[i+1].y, 
										cachedCoords[i+1].z);
								vc = vec3(cachedCoords[i+2].x, 
										cachedCoords[i+2].y, 
										cachedCoords[i+2].z);
								break;
							case 1:
								va = vec3(cachedCoords[i-1].x, 
										cachedCoords[i-1].y, 
										cachedCoords[i-1].z);
								vb = vec3(cachedCoords[i].x, 
										cachedCoords[i].y, 
										cachedCoords[i].z);
								vc = vec3(cachedCoords[i+1].x, 
										cachedCoords[i+1].y, 
										cachedCoords[i+1].z);
								break;
							case 2:
								va = vec3(cachedCoords[i-2].x, 
										cachedCoords[i-2].y, 
										cachedCoords[i-2].z);
								vb = vec3(cachedCoords[i-1].x, 
										cachedCoords[i-1].y, 
										cachedCoords[i-1].z);
								vc = vec3(cachedCoords[i].x, 
										cachedCoords[i].y, 
										cachedCoords[i].z);
								break;
						}
						
						vec3 apn; // approximate normal
						
						int normid = normalIndexTable[cubeindex];
						if(normid < 255)
						{
							apn.x = normalTable[normid][0];
							apn.y = normalTable[normid][1];
							apn.z = normalTable[normid][2];
						}
						else
						{
							apn.x = 0;
							apn.y = 1;
							apn.z = 0;
						}
						
						vec3 u, v, w;
						
						u = vc-vb;
						v = vc-va;
						
						w = cross(u,v);
						
						w = w.normalize();
						
						if (w * apn <=  0){
							w = w*(-1);
						}
						
						/*printf("a: %f %f %f\n", va.x, va.y, va.z);
						printf("b: %f %f %f\n", vb.x, vb.y, vb.z);
						printf("c: %f %f %f\n", vc.x, vc.y, vc.z);
						printf("-----------------------------\n");
						printf("u: %f %f %f\n", u.x, u.y, u.z);
						printf("v: %f %f %f\n", v.x, v.y, v.z);
						printf("normal: %f %f %f\n", w.x,w.y,w.z);*/
						
						n.x = w.x; n.y = w.y; n.z = w.z;
						vertices[tmpcount].n = n;
						tmpcount++;
						//getchar();
					}
				}
			}
		}
	}
	
	printf("SoftwareMarchingCubes: %d vertices set out of a possible %d (%.3f%% fill)\n", vx_count, dim*dim*dim*12, ((float)vx_count/(dim*dim*dim*12))*100);
	
	//// CREATE MESH OBJECT
	
	mesh->setInterleaved(vertices, vx_count-1, indices, vx_count-1);
	return mesh;
}

COORD3D vInterpolation(unsigned int isolevel,
								 COORD3D p1,
								 COORD3D p2,
								 unsigned char v1,
								 unsigned char v2)
{
	double mu;
	COORD3D p;
	
	if (fabs(isolevel-v1)<0.00001) return p1;
	if (fabs(isolevel-v2)<0.00001) return p2;
	if (fabs(v1-v2) < 0.00001) return p1;
	mu = (isolevel - v1) / (v2-v1);
	p.x = p1.x + mu*(p2.x-p1.x);
	p.y = p1.y + mu*(p2.y-p1.y);
	p.z = p1.z + mu*(p2.z-p1.z);
	
	return p;
}
