#ifndef OCL_KERNEL_H
#define OCL_KERNEL_H

#include <CL/cl.h>

class OCLKernel 
{
	public:
		OCLKernel(const char* kernel_path, const char* kernel_name, int device_type = CL_DEVICE_TYPE_GPU);
		~OCLKernel();
		int run(float* data, unsigned int data_count, float* results, unsigned int results_count);
		
	private:
		int m_deviceType;
		const char* m_kernelPath;
		const char* m_kernelSource;
		const char* m_kernelName;
		float* m_data;
		float* m_results;
		unsigned int m_dataCount;
		unsigned int m_resultsCount;
		
		size_t m_local; // local work group size
		size_t m_global; // global work group size
		
		cl_mem m_input; // input buffer
		cl_mem m_output; // output buffer
		
		cl_platform_id m_clpid;   // OpenCL platform
		cl_device_id m_devid;     // compute device id
		cl_context m_ctx;         // compute context
		cl_command_queue m_cmd_q;  // compute command queue
		cl_program m_program;     // compute program
		cl_kernel m_kernel;       // compute kernel
};

#endif
