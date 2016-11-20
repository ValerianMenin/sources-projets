#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

#include "shell_fct.h"

/**
 * un espace autour des pipes et chevrons
 */

int main(int argc, char** argv)
{
	int ret = MYSHELL_CMD_OK;
	cmd mycmd;
	char* readlineptr;
	struct passwd* infos;
	char str[1024];
	char hostname[256];
	char workingdirectory[256];

	const char * readlineFormat = "\nMYSHELL %s@%s:%s$ ";

	while(ret != MYSHELL_FCT_EXIT)
	{
		infos = getpwuid(getuid());
		gethostname(hostname, 256);
		getcwd(workingdirectory, 256);

		snprintf(str, 1024, readlineFormat, infos->pw_name, hostname, workingdirectory);
		readlineptr = readline(str);

		parse_membres(readlineptr, &mycmd);
		parse_membres_args(&mycmd);
		parse_redirection(&mycmd);

		ret = exec_commande(&mycmd);

		free_redirection(&mycmd);
		free_membres_args(&mycmd);
		free_membres(&mycmd);

		free(readlineptr);
	}
	return 0;
}
