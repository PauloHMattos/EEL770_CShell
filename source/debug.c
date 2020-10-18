#include "debug.h"
#include <stdlib.h>
#include "Constants.h"

void log(FILE* file, char* message)
{
    fprintf(file, message);
}

void logDebug(char* message)
{
    #if DEBUG

    log(stdout, "\033[1;36m");
    log(stdout, "[DEBUG]: ");
    log(stdout, "\033[0m");
    log(stdout, message);
    log(stdout, "\n");

    #endif
}

void logError(char* message)
{
    #if DEBUG

    log(stderr, "\033[1;31m");
    log(stderr, "[ERROR]: ");
    log(stderr, "\033[0m");
    log(stderr, message);
    log(stderr, "\n");

    #endif
}

void logWarning(char* message)
{
    #if DEBUG

    log(stdout, "\033[1;33m");
    log(stdout, "[WARNING]: ");
    log(stdout, "\033[0m");
    log(stdout, message);
    log(stdout, "\n");

    #endif
}