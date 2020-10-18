#include <stdio.h>
#include <sys/types.h>
#include "Constants.h"

int state = 0;

/**
 * @brief Executes the basic loop of a shell.
 * 
 * Read: Read the command from the standard input.
 * Parse: Separate the command string into an array of arguments containing the program name.
 * Execute: Run the parsed command.
 */
void loop();

int getCommand(char* command);

int getArguments(char** arguments, int* argumentsCount);

int launchProgram(char* command, char** arguments, int argumentsCount);

void signalHandler(int signalIndex);