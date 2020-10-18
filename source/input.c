#include <stdlib.h>
#include "input.h"

char *readLine(char *line, FILE *stream, uint maxLength)
{
    if (fgets(line, maxLength - 1, stream) != NULL)
    {
        int lastCharId = strlen(line) - 1;
        if(line[lastCharId] == '\n')
        {
        	line[lastCharId] = '\0';
        }
        return line;
    }
    return NULL;
}