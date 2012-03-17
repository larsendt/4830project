#include "OCLKernel.h"
#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

OCLKernel::OCLKernel(const char* kernel_path, int device_type)
{
	m_deviceType = device_type;
	m_kernelPath = kernel_path;
	
	if(m_deviceType == CL_DEVICE_TYPE_GPU)
	{
		printf("OCLKernel using GPU\n");
	}
	else if(m_deviceType == CL_DEVICE_TYPE_CPU)
	{
		printf("OCLKernel using CPU\n");
	}
	else
	{
		fprintf(stderr, "OCLKernel invalid device type: %d\n", m_deviceType);
		exit(EXIT_FAILURE);
	}
	
	cl_int err; // for error code
	
	size_t global; // global domain size for calculation
	size_t local; // local domain size for calculation
	
	cl_platform_id clpid;   // OpenCL platform
	cl_device_id devid;     // compute device id
	cl_context ctx;         // compute context
	cl_command_queue cmd_q;  // compute command queue
	cl_program program;     // compute program
	cl_kernel kernel;       // compute kernel
	
	// connect to a compute device
	err = clGetPlatformIDs(1, &clpid, NULL); // get 1 platform id and stash it in clpid
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to find platform!\n");
		exit(EXIT_FAILURE);
	}
	
	// get a device of the appropriate type
	err = clGetDeviceIDs(clpid, m_deviceType, 1, &devid, NULL); 
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to create a device group!\n");
		exit(EXIT_FAILURE);
	}
	
	// create a compute context
	ctx = clCreateContext(0, 1, &devid, NULL, NULL, &err);
	if(!ctx)
	{
		fprintf(stderr, "Error: Failed to create a compute context!\n");
		exit(EXIT_FAILURE);
	}
	
	// create a command queue
	cmd_q = clCreateCommandQueue(ctx, devid, 0, &err);
	if(!cmd_q)
	{
		fprintf(stderr, "Error: Failed to create a command queue.\n");
		exit(EXIT_FAILURE);
	}
	
	m_kernelSource = readFile(m_kernelPath);
	if(!m_kernelSource)
	{
		fprintf(stderr, "Error: Failed to read kernel file %s\n", m_kernelPath);
		exit(EXIT_FAILURE);
	}
	
	
	printf("Compiling %s...\n", m_kernelPath);
	
}




















