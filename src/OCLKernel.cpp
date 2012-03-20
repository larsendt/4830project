#include "OCLKernel.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Util.h"

static inline int FloorPow2(int n)
{
    int exp;
    frexp((float)n, &exp);
    return 1 << (exp - 1);
}

OCLKernel::OCLKernel(const char* kernel_path, const char* kernel_name, int device_type)
{
	m_deviceType = device_type;
	m_kernelPath = kernel_path;
	m_kernelName = kernel_name;
	
	fprintf(stdout, "Compiling %s...\n", m_kernelPath);
	
	cl_int err; // for error code
	
	// connect to a compute device
	err = clGetPlatformIDs(1, &m_clpid, NULL); // get 1 platform id and stash it in m_clpid
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to find platform!\n");
		print_cl_err(err);
		exit(EXIT_FAILURE);
	}
	
	// get a device of the appropriate type
	err = clGetDeviceIDs(m_clpid, m_deviceType, 1, &m_devid, NULL); 
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to create a device group!\n");
		print_cl_err(err);
		exit(EXIT_FAILURE);
	}
	
	// create a compute context
	m_ctx = clCreateContext(0, 1, &m_devid, NULL, NULL, &err);
	if(!m_ctx || err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to create a compute context!\n");
		print_cl_err(err);
		exit(EXIT_FAILURE);
	}
	
	// create a command queue
	m_cmd_q = clCreateCommandQueue(m_ctx, m_devid, 0, &err);
	if(!m_cmd_q || err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to create a command queue!\n");
		print_cl_err(err);
		exit(EXIT_FAILURE);
	}
	
	m_kernelSource = readFile(m_kernelPath);
	if(!m_kernelSource)
	{
		fprintf(stderr, "Error: Failed to read kernel file %s!\n", m_kernelPath);
		exit(EXIT_FAILURE);
	}
	
	// create the m_program from the source buffer
	m_program = clCreateProgramWithSource(m_ctx, 1, &m_kernelSource, NULL, &err);
	if(!m_program || err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to create program!\n");
		print_cl_err(err);
		exit(EXIT_FAILURE);
	}
	
	// compile the m_program
	err = clBuildProgram(m_program, 0, NULL, NULL, NULL, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to compile program %s\n", m_kernelPath);
		print_cl_err(err);
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
		fprintf(stderr, "Error: Failed to create kernel!\n");
		print_cl_err(err);
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

int OCLKernel::run(int arg_count, OCLArgument* args, 
		          int write_buffer_count, OCLArgument* write_buffers,
		          int read_buffer_count, OCLArgument* read_buffers,
		          int global_width, int global_height)
{
	cl_mem* cl_read_buffers = new cl_mem[read_buffer_count];
	cl_mem* cl_write_buffers = new cl_mem[write_buffer_count];
	cl_int err;
	
	for(int i = 0; i < write_buffer_count; i++)
	{
		cl_write_buffers[i] = clCreateBuffer(m_ctx, CL_MEM_WRITE_ONLY, write_buffers[i].byte_size, write_buffers[i].data, &err);
		if(!cl_write_buffers[i] || err != CL_SUCCESS)
		{
			fprintf(stderr, "Error: Failed to allocate device memory for write buffer %d!\n", i);
			print_cl_err(err);
			return EXIT_FAILURE;
		}
		
		// transfer the input data to device memory
		err = clEnqueueWriteBuffer(m_cmd_q, cl_write_buffers[i], CL_TRUE, 0, write_buffers[i].byte_size, write_buffers[i].data, 0, NULL, NULL);
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Error: Failed to write to input array %d!\n", i);
			print_cl_err(err);
			return EXIT_FAILURE;
		}
	}
	
	for(int i = 0; i < read_buffer_count; i++)
	{
		cl_read_buffers[i] = clCreateBuffer(m_ctx, CL_MEM_READ_ONLY, read_buffers[i].byte_size, read_buffers[i].data, &err);
		if(!cl_read_buffers[i] || err != CL_SUCCESS)
		{
			fprintf(stderr, "Error: Failed to allocate device memory for read buffer %d!\n", i);
			print_cl_err(err);
			return EXIT_FAILURE;
		}
	}

	for(int i = 0; i < arg_count; i++)
	{
		if(args[i].is_buffer)
		{
			cl_mem rbuf = cl_read_buffers[args[i].buffer_index];
			err = clSetKernelArg(m_kernel, i, sizeof(cl_mem), &rbuf);
		}
		else
			err = clSetKernelArg(m_kernel, i, args[i].byte_size, args[i].data);
			
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Error: Failed to set kernel argument %d!\n", i);
			print_cl_err(err);
			return EXIT_FAILURE;
		}
	}

	size_t global[2] = {global_width, global_height};
	size_t local[2];
	
	// get the maximum work group size for executing the kernel on the device
	size_t max = 1;
	err = clGetKernelWorkGroupInfo(m_kernel, m_devid, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &max, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error: Failed to retrieve kernel work group info!\n");
		print_cl_err(err);
		return EXIT_FAILURE;
	}
	
	local[0] = (max > 1) ? FloorPow2(max) : max;  // use nearest power of two (less than max)
	if(local[0] == max)
		local[0] /= 2;
	local[1] = 1;
	
	// execute the kernel over the buffer using the maximum number of work_group items for the device
	err = clEnqueueNDRangeKernel(m_cmd_q, m_kernel, 2, NULL, global, NULL, 0, NULL, NULL);
	if(err != CL_SUCCESS) 
	{
		fprintf(stderr, "%d %d\n", global[0]*global[1], local[0]*local[1]);
		fprintf(stderr, "Error: Failed to execute kernel!\n");
		print_cl_err(err);
		return EXIT_FAILURE;
	}
	
	// wait for the computation to finish
	clFinish(m_cmd_q);
	
	for(int i = 0; i < read_buffer_count; i++)
	{
		// get the results
		err = clEnqueueReadBuffer(m_cmd_q, cl_read_buffers[i], CL_TRUE, 0, read_buffers[i].byte_size, read_buffers[i].data, 0, NULL, NULL);
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Error: Failed to read output array!\n");
			print_cl_err(err);
			return EXIT_FAILURE;
		}
	}
	
	for(int i = 0; i < write_buffer_count; i++)
	{
		clReleaseMemObject(cl_write_buffers[i]);
	}
	
	for(int i = 0; i < read_buffer_count; i++)
	{
		clReleaseMemObject(cl_read_buffers[i]);
	}
	
	return EXIT_SUCCESS;
}
















