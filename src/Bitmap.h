#ifndef BITMAP_H
#define BITMAP_H

// the 2d version of the VoxelCube
class Bitmap
{
	public:
		Bitmap(int dim);
		~Bitmap();
		
		unsigned char at(int x, int y);
		void set(int x, int y, unsigned char data);
		
		int index1d(int x, int y);
		void decompose1dIndex(int index, int* x, int* y);
		
		unsigned char* data() { return m_data; }
		
	private:
		int m_dim;
		unsigned char* m_data;
};

#endif
