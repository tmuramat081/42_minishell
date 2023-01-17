#include "minishell.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"
#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>


void	change_file_descripter(t_process process)
{
	if (ast_count_redirects(process.redirects) > 0)
		set_redirection(process);
	if (process.pipe_state & PIPE_STDIN)
		dup2(process.reader, STDIN_FILENO);
	if (process.pipe_state & PIPE_STDOUT)
		dup2(process.writer, STDOUT_FILENO);
}

/**
 * @brief 外部コマンドを実行する
 *
 * @param args
 * @param msh
 */
void	exec_external_command(t_process process, t_shell *msh)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		change_file_descripter(process);
		ft_execvpe(process.argv[0], process.argv, construct_environ(msh->envs));
		perror("command not found\n");
		exit (EXIT_FAILURE);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	while (waitpid(pid, NULL, 0) <= 0);
	return ;
}