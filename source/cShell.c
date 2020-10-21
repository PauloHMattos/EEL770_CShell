#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "cShell.h"
#include "Constants.h"
#include "input.h"
#include "memory.h"
#include "debug.h"

int main()
{
  	if (signal(SIGUSR1, signalHandler) == SIG_ERR)
	{
		fprintf(stderr, "Erro ao registrar handler de sinal. Execução finalizada");
#if DEBUG
		logError("Não foi possivel registrar o handler do sinal SIGUSR1");
#endif
		return 0;
	}
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
		fprintf(stdin, "Não foi possivel ler o comando. Execução abortada");
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
	fprintf(stdout, "Quantos argumentos você quer digitar? ");
	fscanf(stdin, "%d", argumentsCount);
	
	int count = (*argumentsCount);
	for (int i = 1; i <= count; i++)
	{
		if (checkSignal() != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}

		fprintf(stdout, "Digite o argumento %d: ", i);
		
		char *arg = (char*)malloc(ARGUMENT_BUFFER_SIZE * sizeof(char*));
		if (readLine(arg, stdin, ARGUMENT_BUFFER_SIZE) == NULL)
		{
			fprintf(stdout, "Não foi possivel ler o argumento. Execução abortada");
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
	// Add /bin/ to the command since it's needed for the 'execv' routine 
	char *commandPath = (char*)malloc(strlen(command) + sizeof(BIN_PATH));
	strcpy(commandPath, BIN_PATH);
	strcat(commandPath, command);

	// Assign the command as the first argument. This is needed by 'execv' routine
	arguments[0] = command;

#if DEBUG
	logDebug(commandPath);
	for(int i = 0; i <= argumentsCount; i++)
	{
		logDebug(arguments[i]);
	}
#endif

	pid_t childPid = fork();
	if (childPid == 0)
	{
		int result = execv (commandPath, arguments);

		// Unable to initiate the programam in 'command'
		if (result == -1)
		{
			perror(commandPath);
#if DEBUG
			logError("Não foi possivel iniciar o programa");
#endif
		}
	} 
	else
	{
		wait(NULL);
#if DEBUG
		logDebug("Processo filho finalizado");
#endif
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
	// Safety check
	if (signalIndex == SIGUSR1)
	{
		logDebug("Sinal SIGUSR1 recebido");
		//printf("Sinal SIGUSR1 recebido\n");
		state = 1;
	}
}