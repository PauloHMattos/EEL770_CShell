#include <stdio.h>
#include <sys/types.h>
#include "Constants.h"

/**
 * @brief Executes the basic loop of a shell.
 * 
 * Read: Read the command from the standard input.
 * Parse: Separate the command string into an array of arguments containing the program name.
 * Execute: Run the parsed command.
 */
void loop();