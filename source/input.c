#include <stdlib.h>
#include "input.h"

char *readLine(char* line, FILE* stream, ulong maxLength)
{
    int lastCharId = 0;
    while((lastCharId = getline(&line, &maxLength, stream)) > 0)
    {
        if (lastCharId > 1)
        {
            lastCharId -= 1;
            if(line[lastCharId] == '\n')
            {
                line[lastCharId] = '\0';
            }
            return line;
        }
    }
    return NULL;
}