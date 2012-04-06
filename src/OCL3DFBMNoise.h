#ifndef OCL_3D_FBM_NOISE_H
#define OCL_3D_FBM_NOISE_H

#include "OCLKernel.h"
#include "Types.h"

class OCL3DFBMNoise
{
	public:
		OCL3DFBMNoise();
		bool noise(int dim, unsigned char* data, float pos[3]);
		
	private:
		OCLKernel* m_kernel;
};

#endif
