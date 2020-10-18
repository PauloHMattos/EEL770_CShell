#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "cShell.h"
#include "Constants.h"
#include "input.h"
#include "memory.h"
#include "debug.h"

int main(int argc, char **argv)
{
  	signal(SIGUSR1, signalHandler);
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
		state = 0;
		if ((getCommand(command) != EXIT_SUCCESS) || state != EXIT_SUCCESS)
		{
			continue;
		}

		int argumentsCount = 0;
		if ((getArguments(arguments, &argumentsCount) != EXIT_SUCCESS) || state != EXIT_SUCCESS)
		{
			continue;
		}

		launchProgram(command, arguments, argumentsCount);

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
		logError("Unable to read command. Execution aborted");
		// Invalid line
		return EXIT_FAILURE;
	}

	// Process the command further? 
	// Check for invalid characters, etc
	return EXIT_SUCCESS;
}

int getArguments(char** arguments, int* argumentsCount)
{
	printf("Quantos argumentos você quer digitar? ");
	scanf("%d", argumentsCount);
	//*argumentsCount = 3;

	for (int i = 1; i < (*argumentsCount) + 1; i++)
	{
		//printf("Digite o argumento %d \n", i);
		
		if (readLine(arguments[i], stdin, ARGUMENT_BUFFER_SIZE) == NULL)
		{
			logError("Unable to read argument. Execution aborted");
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int launchProgram(char* command, char** arguments, int argumentsCount)
{
	char *commandPath = (char*)malloc(strlen(command) + sizeof(BIN_PATH));
	strcpy(commandPath, BIN_PATH);
	strcat(commandPath, command);

	logDebug(commandPath);
		arguments[0] = command;
	for(int i = 1; i < argumentsCount + 1; i++)
	{
		logDebug(arguments[i]);
	}

	pid_t childPid = fork();
	if (childPid == 0)
	{
		execvp (commandPath, arguments);
	} 
	else
	{
		wait(NULL);
		logDebug("Child task is done");
	}

	free(commandPath);
	return EXIT_SUCCESS;
}

void signalHandler(int signalIndex)
{
	state = 1;
}