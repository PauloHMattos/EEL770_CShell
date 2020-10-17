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


		char *args = malloc(argumentsCount * sizeof(char));
		for (int i = 0; i < argumentsCount; i++)
		{
			fprintf(stdout, "Digite o argumento %d: \n", i);
		}
		
		fprintf(stdout, "%s %d\n\n", command, argumentsCount);
	} while (status == EXIT_SUCCESS);

	free(command);
}