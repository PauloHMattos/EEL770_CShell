#include "Constants.h"
#include "debug.h"
#include <stdlib.h>


void logMessage(FILE* file, const char* message)
{
    fprintf(file, "%s", message);
}

void logDebug(const char* message)
{
    logMessage(stdout, "\033[1;36m");
    logMessage(stdout, "[DEBUG]: ");
    logMessage(stdout, "\033[0m");
    logMessage(stdout, message);
    logMessage(stdout, "\n");
}

void logError(const char* message)
{
    logMessage(stderr, "\033[1;31m");
    logMessage(stderr, "[ERROR]: ");
    logMessage(stderr, "\033[0m");
    logMessage(stderr, message);
    logMessage(stderr, "\n");
}

void logWarning(const char* message)
{
    logMessage(stdout, "\033[1;33m");
    logMessage(stdout, "[WARNING]: ");
    logMessage(stdout, "\033[0m");
    logMessage(stdout, message);
    logMessage(stdout, "\n");
}