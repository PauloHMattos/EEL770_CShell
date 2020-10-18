#include <stdlib.h>

void freeArray(void** array, int count)
{
	for (int i = 0; i < count; i++)
	{
		free(array[i]);
	}
	free(array);
}