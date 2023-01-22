#include "minishell.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"
#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>


void	change_file_descripter(t_process process)
{
	printf("%d ", process.pipe.reader);
	printf("%d\n", process.pipe.writer);
	close(process.pipe.reader);
	if (process.pipe.state & PIPE_STDIN)
	{
		dup2(process.pipe.reader, STDIN_FILENO);
		close(process.pipe.reader);
	}
	if (process.pipe.state & PIPE_STDOUT)
	{
		dup2(process.pipe.writer, STDOUT_FILENO);
		close(process.pipe.writer);
	}
	if (ast_count_redirects(process.redirects) > 0)
		set_redirection(process);
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
		ft_execvpe(process.argv[0], process.argv, construct_environ(msh->envs));
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		exit(EXIT_FAILURE);
	}
}