__kernel void square(__global float* input, 
                     const unsigned int input_size, 
                     __global float* output, 
                     const unsigned int output_size)
{
	int i = get_global_id(0);
	if(i < input_size)
		output[i] = input[i] * input[i];
}

