#include "terminal.h"

void	shell_perror(char *string, t_shell *msh)
{
	extern int	g_status;

	if (msh && msh->prompt)
		ft_putstr_fd(msh->prompt, STDERR_FILENO);
	perror(string);
	if (msh->is_child_process == false)
		return ;
	exit(g_status);
}

