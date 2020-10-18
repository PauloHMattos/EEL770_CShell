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
		return -1;
	}

	// Process the command further? 
	// Check for invalid characters, etc
	return 0;
}

int getArguments(char** arguments, int* argumentsCount)
{
	printf("Quantos argumentos você quer digitar? ");
	//scanf("%d", argumentsCount);
	argumentsCount = 3;

	for (int i = 0; i < argumentsCount; i++)
	{
		printf("Digite o argumento %d \n", i + 1);
		
		if (readLine(arguments[i], stdin, ARGUMENT_BUFFER_SIZE) == NULL)
		{
			logError("Unable to read argument. Execution aborted");
			return -1;
		}
	}
	return 0;
}

int launchProgram(char* command, char** arguments, int argumentsCount)
{
	pid_t childPid = fork();
	if (childPid == 0)
	{
		char *commandPath = (char*)malloc(strlen(command) + sizeof(BIN_PATH));
		strcpy(commandPath, BIN_PATH);
		strcat(commandPath, command);


		logDebug(commandPath);
		for(int i = 0; i < argumentsCount; i++)
		{
			logDebug(arguments[i]);
		}

		execvp(commandPath, arguments);
		free(commandPath);
		return 0;
	} 
	else
	{
		wait(NULL);
		logDebug("Task is done");
		return 0;
	}
}