#include "terminal.h"

/**
 * @brief
 * @detail 仕様上、EISDIRのみ"Is a directory"を"is a dorectory"に置き換える。
 * @param string
 * @param msh
 * @param status
 */
void	shell_perror(const char *string, t_shell *msh, int status)
{
	ft_putstr_fd("m-shell: ", STDERR_FILENO);
	if (errno == EISDIR)
		ft_putendl_fd("is a directory", STDERR_FILENO);
	else
		perror(string);
	if (msh && msh->is_child_process == false)
		return ;
	exit(status);
}
