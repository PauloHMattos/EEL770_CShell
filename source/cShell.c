#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "cShell.h"

int main(int argc, char **argv)
{
	loop();
	return EXIT_SUCCESS;
}

void loop()
{
	int status = 0;

	do
	{
		int argumentsCount = 0;
		char* command = getCommand();
		char** arguments = getArguments(&argumentsCount);
		
		fprintf(stdout, "%s", command);
		for (int i = 0; i < argumentsCount; i++)
		{
			fprintf(stdout, " %s", arguments[i]);
		}
		fprintf(stdout, "\n\n");

		free(command);
		freeArray(arguments, argumentsCount);
	} while (status == EXIT_SUCCESS);

}

char* getCommand()
{
	char* command = (char*)malloc(COMMAND_BUFFER_SIZE * sizeof(char));
	fprintf(stdout, "Qual comando quer executar? ");
	fscanf(stdin, "%s", command);
	return command;
}

char** getArguments(int* argumentsCount)
{
	fprintf(stdout, "Quantos argumentos você quer digitar? ");
	fscanf(stdin, "%d", argumentsCount);

	char** args = (char**)malloc(*argumentsCount * sizeof(char*));

	for (int i = 0; i < *argumentsCount; i++)
	{
		fprintf(stdout, "Digite o argumento %d: ", i + 1);

		args[i] = (char*)malloc(ARGUMENT_BUFFER_SIZE * sizeof(char));
		fscanf(stdin, "%s", args[i]);
	}
	return args;
}

void freeArray(void** array, int count)
{
	for (int i = 0; i < count; i++)
	{
		free(array[i]);
	}
	free(array);
}