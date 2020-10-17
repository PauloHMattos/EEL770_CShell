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
	char command[COMMAND_BUFFER_SIZE];
	char **args;
	int argumentsCount = 0;

	do
	{
		fprintf(stdout, "Qual comando quer executar? ");

		fscanf(stdin, "%s", &command);

		fprintf(stdout, "Quantos argumentos você quer digitar? ");
		fscanf(stdin, "%d", &argumentsCount);


		char** args = (char**)malloc(argumentsCount * sizeof(char*));

		for (int i = 0; i < argumentsCount; i++)
		{
			fprintf(stdout, "Digite o argumento %d: ", i + 1);

			char* arg = (char*)malloc(ARGUMENT_BUFFER_SIZE * sizeof(char));
			fscanf(stdin, "%s", arg);
			args[i] = arg;
		}
		
		fprintf(stdout, "%s", command);
		for (int i = 0; i < argumentsCount; i++)
		{
			fprintf(stdout, " %s", args[i]);
		}
		fprintf(stdout, "\n");

	} while (status == EXIT_SUCCESS);

	free(command);
}