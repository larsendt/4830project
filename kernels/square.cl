__kernel void square(__global float* input, 
                     const unsigned int input_size, 
                     __global float* output, 
                     const unsigned int output_size)
{
	int id = get_global_id(0);
	output[id] = 0;
	for(int i = 0; i < input_size; i++)
	{
		output[id] += input[i];
	}
}

