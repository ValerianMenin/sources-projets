#include "shell_fct.h"

static pid_t * children;
static size_t childrenCount = 0;

void watchdog(int sig)
{
	unsigned int i;

	if(children == NULL)
		return;

	for(i = 0; i < childrenCount; ++i)
	{
		kill(children[i], SIGTERM);
	}
}

int exec_commande(cmd* c)
{
	unsigned int i;
	int ** pipes;

	pipes = (int**)malloc(c->nb_cmd_membres * sizeof(int*));
	if(pipes == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	children = (pid_t*)malloc(c->nb_cmd_membres * sizeof(pid_t));
	if(children == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	/* pipe[0][0] close
	   pipe[0][1] stdout

	   pipe[0][0] stdin
	   pipe[1][1] stdout

	   pipe[1][0]
	   pipe[2][1] ...
	*/

	for(i = 0; i < c->nb_cmd_membres; ++i)
	{
		pipes[i] = (int*)malloc(2 * sizeof(int));
		if(pipes[i] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		pipe(pipes[i]);

		children[i] = fork();
		if(children[i] == 0)
		{
			// Redirect stdin except for first process whom won't read from pipe
			if(i > 0)
			{
				dup2(pipes[i - 1][0], fileno(stdin));
				close(pipes[i - 1][0]);
			}
			else
			{
				close(pipes[i][0]);
			}

			dup2(pipes[i][1], fileno(stdout));
			close(pipes[i][1]);

			/* Wait for last process to finish */
			if(i >  0)
				waitpid(children[i - 1], NULL, 0);

			if(execvp(c->cmd_membres_args[i][0], c->cmd_membres_args[i]) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
			break;
		}
		childrenCount++;
	}

	/* The following code is only executed by the parent process */

	/* Configure pipe */
	char buffer[1024];
	int _stdin = dup(fileno(stdin));
	close(fileno(stdin));

	close(pipes[i - 1][1]);
	dup2(pipes[i - 1][0], fileno(stdin));
	close(pipes[i - 1][0]);

	/* Set watchdog */
	signal(SIGALRM, watchdog);
	alarm(5);

	/* Wait children */
	for(i = 0; i < c->nb_cmd_membres; ++i)
	{
		waitpid(children[i], NULL, 0);
	}

	/* Read from pipe */
	while(fgets(buffer, 1024, stdin) != NULL)
		printf("%s", buffer);

	free(pipes);
	pipes = NULL;

	free(children);
	children = NULL;

	dup2(_stdin, fileno(stdin));

	return MYSHELL_CMD_OK;
}