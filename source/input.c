#include <stdlib.h>
#include "input.h"

char *readLine(char *line, FILE *stream, ulong maxLength)
{
    int lastCharId = getline(&line, &maxLength, stream);
    if (lastCharId != 0)
    {
        lastCharId -= 1;
        if(line[lastCharId] == '\n')
        {
        	line[lastCharId] = '\0';
        }
        return line;
    }
    return NULL;
}