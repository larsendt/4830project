#ifndef NOISE_CUBE_H
#define NOISE_CUBE_H

// a data class that stores noise data as a 1d 
// contiguous array, for ease of use in OpenCL and VBOs

class VoxelCube
{
	public:
		VoxelCube(int dim);
		~VoxelCube();
		
		unsigned char at(int x, int y, int z);
		void set(int x, int y, int z, unsigned char data);
		
		int index1d(int x, int y, int z);
		void decompose1dIndex(int index, int* x, int* y, int* z);
		void addFloor();
		
		unsigned char* data() { return m_data; }
		int max1dIndex() { return m_dim * m_dim * m_dim; }
		int dimension() { return m_dim; }
		
		VoxelCube& operator-(VoxelCube other);
		VoxelCube& operator+(VoxelCube other);
		
	private:
		unsigned char* m_data;
		int m_dim;
};
		
#endif
