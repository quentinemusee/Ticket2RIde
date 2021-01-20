#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "GamePhase.h"
#include "TicketToRideAPI.h"

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	while (1)
	{
		char *args[2] = {
			"main.out",
			NULL
		};

		pid_t pid = fork();

		if (pid == -1)
		{
			fprintf(stderr, "ERROR : unknown problem.\n");
			exit(EXIT_FAILURE);
		}

		if (!pid)
		{
	    	execv("main.out", args);
			fprintf(stderr, "ERROR : program A not found.\n");
			exit(EXIT_FAILURE);
		}
		
		wait(NULL);
	}

	return EXIT_SUCCESS;
}