#include "execution.h"
#include "minishell.h"

int builtin_exit(char **args, t_shell *msh)
{
	(void)args;
	(void)msh;
	exit(0);
	return (0);
}