#include "terminal.h"

void	maybe_exit(int status, t_shell *msh)
{
	extern int	g_status;

	if (msh && msh->is_child_process == false)
	{
		g_status = status;
		return ;
	}
	exit(status);
}

/**
 * @brief
 * @detail 仕様上、errnoがEISDIRである場合のみ"Is a directory"を"is a dorectory"に置き換える。
 * @param string　
 * @param msh シェルの管理情報
 * @param status
 */
void	shell_perror(const char *string, t_shell *msh, int status)
{
	extern int	g_status;

	ft_putstr_fd("m-shell: ", STDERR_FILENO);
	if (errno == EISDIR)
		ft_putendl_fd("is a directory", STDERR_FILENO);
	else
		perror(string);
	return (maybe_exit(status, msh));
}
