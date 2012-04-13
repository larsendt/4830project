#include "Bitmap.h"

Bitmap::Bitmap(int dim)
{
	m_dim = dim;
	m_data = new unsigned char[dim*dim];
}	

Bitmap::~Bitmap()
{
	delete[] m_data;
}

unsigned char Bitmap::at(int x, int y)
{
	return m_data[index1d(x, y)];
}

void Bitmap::set(int x, int y, unsigned char value)
{
	m_data[index1d(x, y)] = value;
}

int Bitmap::index1d(int x, int y)
{
	return (x*m_dim) + y;
}

void Bitmap::decompose1dIndex(int index, int* x, int* y)
{
	*x = index/m_dim;
	*y = index - (*x*m_dim);
}
