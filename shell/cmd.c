#include "cmd.h"

void parse_membres(char *chaine, cmd *ma_cmd)
{
	ma_cmd->cmd_initiale = strdup(chaine);
	ma_cmd->nb_cmd_membres = 0;
	ma_cmd->cmd_membres = NULL;

	char * ptr = strtok(chaine, "|");

	while(ptr != NULL)
	{
		ma_cmd->cmd_membres = (char**)realloc(ma_cmd->cmd_membres, (ma_cmd->nb_cmd_membres + 1) * sizeof(char*));
		if(ma_cmd->cmd_membres == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}

		ma_cmd->cmd_membres[ma_cmd->nb_cmd_membres] = strdup(ptr);

		ma_cmd->nb_cmd_membres++;

		ptr = strtok(NULL, "|");
	}
}

void aff_membres(cmd *ma_cmd)
{
	unsigned int i;

	printf("Listing command members :\n");

	for(i = 0; i < ma_cmd->nb_cmd_membres; ++i)
		printf(" * %s\n", ma_cmd->cmd_membres[i]);
}

void free_membres(cmd *ma_cmd)
{
	unsigned int i;

	ma_cmd->nb_cmd_membres = 0;

	for(i = 0; i < ma_cmd->nb_cmd_membres; ++i)
	{
		free(ma_cmd->cmd_membres[i]);
	}

	free(ma_cmd->cmd_membres);
	ma_cmd->cmd_membres = NULL;
}

void aff_membres_args(cmd *c)
{
	unsigned int i, j;

	printf("Listing arguments of all members :\n");

	for(i = 0; i < c->nb_cmd_membres; ++i)
	{
		printf("* Member : %s\n", c->cmd_membres[i]);

		for(j = 0; j < c->nb_membres_args[i]; ++j)
			printf("\t- Arg : %s\n", c->cmd_membres_args[i][j]);

	}
}

/* SEGFAULT HERE */
void free_membres_args(cmd *c)
{
	unsigned int i, j;

	for(i = 0; i < c->nb_cmd_membres; ++i)
	{
		for(j = 0; j < c->nb_membres_args[i]; ++j)
			free(c->cmd_membres_args[i][j]);

		free(c->cmd_membres_args[i]);
	}

	free(c->cmd_membres_args);

	c->cmd_membres_args = NULL;
}

void parse_membres_args(cmd *c)
{
	unsigned int i;

	c->nb_membres_args = (unsigned int *)malloc(c->nb_cmd_membres * sizeof(unsigned int));
	if(c->nb_membres_args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	c->cmd_membres_args = (char***)malloc(c->nb_cmd_membres * sizeof(char**));
	if(c->cmd_membres_args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}


	for(i = 0; i < c->nb_cmd_membres; ++i)
	{
		char * str = strdup(c->cmd_membres[i]); // Dup string to avoid alteration
		char * ptr = strtok(str, " ");

		c->cmd_membres_args[i] = NULL;
		c->nb_membres_args[i] = 0;

		while(ptr != NULL)
		{
			c->cmd_membres_args[i] = (char**)realloc(c->cmd_membres_args[i], (c->nb_membres_args[i] + 1) * sizeof(char*));
			if(c->cmd_membres_args[i] == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}

			c->cmd_membres_args[i][c->nb_membres_args[i]] = strdup(ptr);

			c->nb_membres_args[i]++;

			ptr = strtok(NULL, " ");
		}

		/* Add a NULL argument */
		c->cmd_membres_args[i] = (char**)realloc(c->cmd_membres_args[i], (c->nb_membres_args[i] + 1) * sizeof(char*));
		if(c->cmd_membres_args[i] == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		c->cmd_membres_args[i][c->nb_membres_args[i]] = NULL;
		c->nb_membres_args[i]++;


		free(str);
	}
}

void parse_redirection(cmd *c)
{
	unsigned int i, j;

	/* Allocate */
	c->redirection = (char***)malloc(c->nb_cmd_membres * sizeof(char**));
	if(c->redirection == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	c->type_redirection = (int**)malloc(c->nb_cmd_membres * sizeof(int*));
	if(c->type_redirection == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < c->nb_cmd_membres; ++i)
	{
		c->redirection[i] = (char**)malloc(3 * sizeof(char*));
		if(c->redirection[i] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		memset(c->redirection[i], 0, 3);

		c->type_redirection[i] = (int*)malloc(3 * sizeof(int));
		if(c->type_redirection[i] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		memset(c->type_redirection[i], DEFAULT, 3);
	}

	/* Compare */
	for(i = 0; i < c->nb_cmd_membres; ++i)
	{
		for(j = 0; j < c->nb_membres_args[i]; ++j)
		{
			if(c->cmd_membres_args[i][j] == NULL)
					break;

			/* STDOUT*/
			if(strcmp(c->cmd_membres_args[i][j], ">") == 0)
			{
				c->redirection[i][STDOUT] = c->cmd_membres_args[i][j + 1];
				c->type_redirection[i][STDOUT] = DEFAULT;
				continue;
			}

			if(strcmp(c->cmd_membres_args[i][j], ">>") == 0)
			{
				c->redirection[i][STDOUT] = c->cmd_membres_args[i][j + 1];
				c->type_redirection[i][STDOUT] = APPEND;
				continue;
			}

			/* STDERR */
			if(strcmp(c->cmd_membres_args[i][j], "2>") == 0)
			{
				c->redirection[i][STDERR] = c->cmd_membres_args[i][j + 1];
				c->type_redirection[i][STDERR] = DEFAULT;
				continue;
			}

			if(strcmp(c->cmd_membres_args[i][j], "2>>") == 0)
			{
				c->redirection[i][STDERR] = c->cmd_membres_args[i][j + 1];
				c->type_redirection[i][STDERR] = APPEND;
				continue;
			}

			/* STDIN */
			if(strcmp(c->cmd_membres_args[i][j], "<") == 0)
			{
				c->redirection[i][STDIN] = c->cmd_membres_args[i][j + 1];
				c->type_redirection[i][STDIN] = DEFAULT;
			}
		}
	}
}

void free_redirection(cmd *c)
{
	unsigned int i;

	for(i = 0; i < c->nb_cmd_membres; ++i)
	{
		free(c->redirection[i]);
		free(c->type_redirection[i]);
	}

	free(c->redirection);
	c->redirection = NULL;

	free(c->type_redirection);
	c->type_redirection = NULL;
}


void aff_redirection(cmd c)
{
	unsigned int i;
	for(i = 0; i < c.nb_cmd_membres; ++i)
	{
		printf(" * STDOUT : %s [%d]\n", c.redirection[i][STDOUT], c.type_redirection[i][STDOUT]);
		printf(" * STDERR : %s [%d]\n", c.redirection[i][STDERR], c.type_redirection[i][STDERR]);
		printf(" * STDIN : %s [%d]\n", c.redirection[i][STDIN], c.type_redirection[i][STDIN]);
	}
}

