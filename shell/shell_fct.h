#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "cmd.h"

#define MYSHELL_CMD_OK		1
#define MYSHELL_FCT_EXIT 	2

int exec_commande(cmd* ma_cmd);