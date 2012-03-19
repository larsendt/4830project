#ifndef OCL_NOISE_H
#define OCL_NOISE_H

#include "OCLKernel.h"

enum NoiseType 
{
	GRADIENT,
	TURBULENCE,
	MONOFRACTAL,
	MULTIFRACTAL
};

class OCLNoise 
{
	public:
		OCLNoise();
		int noise2D(NoiseType type, int dim, unsigned char* data);
	
	private:
		int gradientNoise2D(int dim, unsigned char* data);
		int turbulence2D(int dim, unsigned char* data);
		int monoFractal2D(int dim, unsigned char* data);
		int multiFractal2D(int dim, unsigned char* data);
		
		OCLKernel* m_gradientKernel;
		OCLKernel* m_turbulenceKernel;
		OCLKernel* m_monoFractalKernel;
		OCLKernel* m_multiFractalKernel;
};

#endif
