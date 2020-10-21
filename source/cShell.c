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

	do
	{
		state = 0;
		for (int i = 0; i < MAX_ARGUMENTS_COUNT; i++)
		{
			arguments[i] = NULL;
		}

		if (getCommand(command) != EXIT_SUCCESS)
		{
			continue;
		}

		int argumentsCount = 0;
		if (getArguments(arguments, &argumentsCount) != EXIT_SUCCESS)
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
	fprintf(stdout, "Qual comando quer executar? ");
	if (readLine(command, stdin, COMMAND_BUFFER_SIZE) == NULL)
	{
		logError("Unable to read command. Execution aborted");
		// Invalid line
		return EXIT_FAILURE;
	}

	if (checkSignal() != EXIT_SUCCESS)
	{
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
	
	int count = (*argumentsCount);
	for (int i = 1; i <= count; i++)
	{
		if (checkSignal() != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}

		printf("Digite o argumento %d: ", i);
		
		char *arg = (char*)malloc(ARGUMENT_BUFFER_SIZE * sizeof(char*));
		if (readLine(arg, stdin, ARGUMENT_BUFFER_SIZE) == NULL)
		{
			logError("Unable to read argument. Execution aborted");
			return EXIT_FAILURE;
		}
		arguments[i] = arg;
	}

	// Make sure the argument after the read ones is null
	arguments[count + 1] = NULL;
	return EXIT_SUCCESS;
}

int launchProgram(char* command, char** arguments, int argumentsCount)
{
	char *commandPath = (char*)malloc(strlen(command) + sizeof(BIN_PATH));
	strcpy(commandPath, BIN_PATH);
	strcat(commandPath, command);

	logDebug(commandPath);
	arguments[0] = command;
	for(int i = 0; i <= argumentsCount; i++)
	{
		logDebug(arguments[i]);
	}

	pid_t childPid = fork();
	if (childPid == 0)
	{
		execv (commandPath, arguments);
	} 
	else
	{
		wait(NULL);
		logDebug("Child task is done");
	}

	free(commandPath);
	return EXIT_SUCCESS;
}

int checkSignal()
{
	if (state == 0)
	{
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

void signalHandler(int signalIndex)
{
	state = 1;
}