#include "Util.h"
#include <stdio.h>
#include <stdlib.h>

#define INIT_SZ 4096

char* readFile(const char* filename)
{
	FILE* f = fopen(filename, "r");
	char* text = NULL;
	
	if(f)
	{
		fseek(f, 0, SEEK_END);
		long pos = ftell(f);
		fseek(f, 0, SEEK_SET);
		
		text = (char*)malloc(pos * sizeof(char));
		fread(text, pos, 1, f);
		fclose(f);		
	}
    
    return text;
}
