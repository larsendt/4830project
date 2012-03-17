#include <stdio.h>
#include "OCLKernel.h"

int main(int argc, char** argv)
{
	OCLKernel* k = new OCLKernel("kernels/square.ocl");
	delete k;
	return 0;
}
