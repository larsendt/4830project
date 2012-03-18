#include "OCLKernel.h"
#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

OCLKernel::OCLKernel(const char* kernel_path, const char* kernel_name, int device_type)
{
	m_deviceType = device_type;
	m_kernelPath = kernel_path;
	m_kernelName = kernel_name;
	
	fprintf(stdout, "Compiling %s...\n", m_kernelName);
	
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
	
	// connect to a compute device
	err = clGetPlatformIDs(1, &m_clpid, NULL); // get 1 platform id and stash it in m_clpid
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to find platform!\n");
		exit(EXIT_FAILURE);
	}
	
	// get a device of the appropriate type
	err = clGetDeviceIDs(m_clpid, m_deviceType, 1, &m_devid, NULL); 
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to create a device group!\n");
		exit(EXIT_FAILURE);
	}
	
	// create a compute context
	m_ctx = clCreateContext(0, 1, &m_devid, NULL, NULL, &err);
	if(!m_ctx)
	{
		fprintf(stderr, "Error: Failed to create a compute context!\n");
		exit(EXIT_FAILURE);
	}
	
	// create a command queue
	m_cmd_q = clCreateCommandQueue(m_ctx, m_devid, 0, &err);
	if(!m_cmd_q)
	{
		fprintf(stderr, "Error: Failed to create a command queue!\n");
		exit(EXIT_FAILURE);
	}
	
	m_kernelSource = readFile(m_kernelPath);
	if(!m_kernelSource)
	{
		fprintf(stderr, "Error: Failed to read m_kernel file %s!\n", m_kernelPath);
		exit(EXIT_FAILURE);
	}
	
	// create the m_program from the source buffer
	m_program = clCreateProgramWithSource(m_ctx, 1, &m_kernelSource, NULL, &err);
	if(!m_program)
	{
		fprintf(stderr, "Error: Failed to create m_program!\n");
		exit(EXIT_FAILURE);
	}
	
	// compile the m_program
	err = clBuildProgram(m_program, 0, NULL, NULL, NULL, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to compile m_program %s\n", m_kernelName);
		size_t len;
		char buffer[2048];
		clGetProgramBuildInfo(m_program, m_devid, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		fprintf(stderr, "%s\n", buffer);
		exit(EXIT_FAILURE);
	}
	
	// create the m_kernel in the m_program
	m_kernel = clCreateKernel(m_program, m_kernelName, &err);
	if(!m_kernel || err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to create m_kernel!\n");
		exit(EXIT_FAILURE);
	}
}

OCLKernel::~OCLKernel()
{
	clReleaseProgram(m_program);
	clReleaseKernel(m_kernel);
	clReleaseCommandQueue(m_cmd_q);
	clReleaseContext(m_ctx);
}

int OCLKernel::run(float* data, unsigned int data_count, float* results, unsigned int results_count)
{
	m_data = data;
	m_dataCount = data_count;
	m_results = results;
	m_resultsCount = results_count;	
	
	// create the device memory buffers
	m_input = clCreateBuffer(m_ctx, CL_MEM_READ_ONLY, sizeof(float) * m_dataCount, NULL, NULL);
	m_output = clCreateBuffer(m_ctx, CL_MEM_WRITE_ONLY, sizeof(float) * m_resultsCount, NULL, NULL);

	if(!m_input || !m_output)
	{
		fprintf(stderr, "Error: Failed to allocate device memory!\n");
		return EXIT_FAILURE;
	}
	
	cl_int err;
	
	// transfer the input data to device memory
	err = clEnqueueWriteBuffer(m_cmd_q, m_input, CL_TRUE, 0, sizeof(float) * m_dataCount, m_data, 0, NULL, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to write to input array!\n");
		return EXIT_FAILURE;
	}
	
	// set the arguments to the compute kernel
	err = 0;
	err = clSetKernelArg(m_kernel, 0, sizeof(cl_mem), &m_input);
	err |= clSetKernelArg(m_kernel, 1, sizeof(unsigned int), &m_dataCount);
	err |= clSetKernelArg(m_kernel, 2, sizeof(cl_mem), &m_output);
	err |= clSetKernelArg(m_kernel, 3, sizeof(unsigned int), &m_resultsCount);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to set kernel arguments!\n");
		return EXIT_FAILURE;
	}
	
	// get the maximum work group size for executing the kernel on the device
	err = clGetKernelWorkGroupInfo(m_kernel, m_devid, CL_KERNEL_WORK_GROUP_SIZE, sizeof(m_local), &m_local, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to retrieve kernel work group info!\n");
		return EXIT_FAILURE;
	}
	
	// execute the kernel over the buffer using the maximum number of work_group items for the device
	m_global = m_dataCount;
	err = clEnqueueNDRangeKernel(m_cmd_q, m_kernel, 1, NULL, &m_global, &m_local, 0, NULL, NULL);
	if(err != CL_SUCCESS) 
	{
		fprintf(stderr, "Error: Failed to execute kernel!\n");
		return EXIT_FAILURE;
	}
	
	// wait for the computation to finish
	clFinish(m_cmd_q);
	
	// get the results
	err = clEnqueueReadBuffer(m_cmd_q, m_output, CL_TRUE, 0, sizeof(float) * m_resultsCount, m_results, 0, NULL, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to read output array!\n");
		return EXIT_FAILURE;
	}
	
	clReleaseMemObject(m_input);
	clReleaseMemObject(m_output);
	
	printf("Finished executing %s\n", m_kernelName);
	return EXIT_SUCCESS;
}
















