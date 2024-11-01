#include <stdio.h>
#include <string.h>
#include "global.h"

void concatenate (char* str1, char* str2, char* out, size_t size)
{
	snprintf(out, size, "%s%s", str1, str2);
}

bool file_exists (char* filepath)
{
	FILE* file = fopen(filepath, "r+");

	if(file == NULL)
	{
		return false;
	}

	fclose(file);

	return true;
}
