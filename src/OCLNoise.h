#ifndef OCL_NOISE_H
#define OCL_NOISE_H

#include "OCLKernel.h"

class OCLNoise 
{
	public:
		OCLNoise();
		int noise2D(int dim, unsigned char* data);
	
	private:
		OCLKernel* m_kernel;
};

#endif
