#ifndef OCL_KERNEL_H
#define OCL_KERNEL_H

#include <CL/cl.h>

class OCLKernel 
{
	public:
		OCLKernel(const char* kernel_path, int device_type = CL_DEVICE_TYPE_GPU);
		
	private:
		int m_deviceType;
		const char* m_kernelPath;
		const char* m_kernelSource;
};

#endif
