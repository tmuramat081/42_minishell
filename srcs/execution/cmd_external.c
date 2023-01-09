#include "minishell.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"
#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief 外部コマンドを実行する
 *
 * @param args
 * @param msh
 */
void	exec_external_command(char **args, t_process process, t_shell *msh)
{
	pid_t	pid;
	(void)msh;
	(void)process;

	pid = fork();
	if (pid == 0)
	{
		ft_execvpe(args[0], args, construct_environ(msh->envs));
		perror("command not found\n");
		exit (EXIT_FAILURE);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	while (waitpid(pid, NULL, 0) <= 0);
	return ;
}