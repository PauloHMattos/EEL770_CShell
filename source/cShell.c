#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "cShell.h"
#include "Constants.h"
#include "input.h"
#include "memory.h"

int main(int argc, char **argv)
{
	loop();
	return EXIT_SUCCESS;
}

void loop()
{
	int status = 0;
	char* command = (char*)malloc(COMMAND_BUFFER_SIZE* sizeof(char*));
	char** arguments = (char**)malloc(MAX_ARGUMENTS_COUNT * sizeof(char*));
	for (int i = 0; i < MAX_ARGUMENTS_COUNT; i++)
	{
		arguments[i] = (char*)malloc(ARGUMENT_BUFFER_SIZE * sizeof(char*));
	}

	do
	{
		int argumentsCount = 0;
		int commandStatus = getCommand(command);
		int argumentsStatus = getArguments(arguments, &argumentsCount);
		
		fprintf(stdout, "%s", command);
		for (int i = 0; i < argumentsCount; i++)
		{
			fprintf(stdout, " %s", arguments[i]);
		}
		fprintf(stdout, "\n\n");
	} while (status == EXIT_SUCCESS);

	free(command);
	for (int i = 0; i < MAX_ARGUMENTS_COUNT; i++)
	{
		free(arguments[i]);
	}
	free(arguments);
}

int getCommand(char* command)
{
	fprintf(stdout, "Qual comando quer executar?\n");
	if (readLine(command, stdin, COMMAND_BUFFER_SIZE) == NULL)
	{
		// Invalid line
		return -1;
	}

	// Process the command further? 
	// Check for invalid characters, etc
	return 0;
}

int getArguments(char** arguments, int* argumentsCount)
{
	fprintf(stdout, "Quantos argumentos você quer digitar? ");
	fscanf(stdin, "%d", argumentsCount);
	
	for (int i = 0; i < *argumentsCount; i++)
	{
		fprintf(stdout, "Digite o argumento %d: ", i + 1);

		if (readLine(arguments[i], stdin, ARGUMENT_BUFFER_SIZE) == NULL)
		{
			return -1;
		}
		//fprintf(stdout, "\n");
	}
	return 0;
}
