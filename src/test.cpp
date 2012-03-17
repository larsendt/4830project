// You might need to change this header based on your install:
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>

static void check_error(cl_int error, char* name) {
    if (error != CL_SUCCESS) {
        fprintf(stderr, "Non-successful return code %d for %s.  Exiting.\n", error, name);
        exit(1);
    }
}

int main (int argc, char const *argv[])
{
    cl_uint i;
    cl_int err;

    // Discover the number of platforms:
    cl_uint nplatforms;
    err = clGetPlatformIDs(0, NULL, &nplatforms);
    check_error(err, "clGetPlatformIds");

    // Now ask OpenCL for the platform IDs:
    cl_platform_id* platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * nplatforms);
    err = clGetPlatformIDs(nplatforms, platforms, NULL);
    check_error(err, "clGetPlatformIds");

    // Ask OpenCL about each platform to understand the problem:
    char name[128];
    char vendor[128];
    char version[128];

    fprintf(stdout, "OpenCL reports %d platforms.\n\n", nplatforms);

    for (i = 0; i < nplatforms; i++) {
        err |= clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 128, vendor, NULL);
        err |= clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 128, name, NULL);
        err |= clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, 128, version, NULL);
        check_error(err, "clGetPlatformInfo");

        fprintf(stdout, "Platform %d: %s %s %s\n", i, vendor, name, version);
    }

    free(platforms);
    return 0;
}
