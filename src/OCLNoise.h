#ifndef OCL_NOISE_H
#define OCL_NOISE_H

#include "OCLKernel.h"

enum NoiseType 
{
	GRADIENT,
	FBM,
	TURBULENCE,
	MONOFRACTAL,
	MULTIFRACTAL,
	RIDGEDMULTIFRACTAL,
};

class OCLNoise 
{
	public:
		OCLNoise();
		bool noise2D(NoiseType type, int dim, unsigned char* data);
		bool noise3D(NoiseType type, int dim, unsigned char* data);
	
	private:
		bool gradientNoise2D(int dim, unsigned char* data);
		bool turbulence2D(int dim, unsigned char* data);
		bool monoFractal2D(int dim, unsigned char* data);
		bool multiFractal2D(int dim, unsigned char* data);
		bool fbmNoise2D(int dim, unsigned char* data);

		bool gradientNoise3D(int dim, unsigned char* data);
		bool fbmNoise3D(int dim, unsigned char* data);
		bool turbulence3D(int dim, unsigned char* data);
		bool multiFractal3D(int dim, unsigned char* data);
		bool ridgedMultiFractal3D(int dim, unsigned char* data);
		
		OCLKernel* m_gradientKernel;
		OCLKernel* m_fbmKernel;
		OCLKernel* m_turbulenceKernel;
		OCLKernel* m_monoFractalKernel;
		OCLKernel* m_multiFractalKernel;
		OCLKernel* m_gradient3dKernel;
		OCLKernel* m_fbm3dKernel;
		OCLKernel* m_multiFractal3dKernel;
		OCLKernel* m_turbulence3dKernel;
		OCLKernel* m_ridgedMultiFractal3dKernel;
};

#endif
