#include "execution.h"
#include "libast.h"
#include <signal.h>

char* prompt = NULL;


void	pipe_create(t_pipe *piped)
{
	int	tmp[2];

	if (pipe(tmp) < 0)
	{
		exit(EXIT_FAILURE);
	}
	piped->reader = tmp[0];
	piped->writer = tmp[1];
}

void	pipe_delete(t_pipe *piped)
{
	dup2(piped->reader, STDIN_FILENO);
	dup2(piped->writer, STDOUT_FILENO);
	close(piped->reader);
	close(piped->writer);
}

t_pipe	pipe_init(void)
{
	t_pipe piped;

	piped.reader = STDIN_FILENO;
	piped.writer = STDOUT_FILENO;
	return (piped);
}

void wait_child_process(void)
{
	int		status;

    while (waitpid(-1, &status, 0) <= 0);
}


void	exec_pipeline_recursive(t_ast_node *node, t_process process, t_shell *msh, int in_fd)
{
	int	fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(in_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		exec_simple_cmd(node->left, process, msh);
		return ;
	}
	else
	{
		close(fd[1]);
		close(in_fd);
		if (node->right->type & NODE_PIPELINE)
			exec_pipeline_recursive(node->right, process, msh, fd[0]);
	}
	if (node->right->type & NODE_COMMAND)
	{
		dup2(fd[0], STDIN_FILENO);
		exec_simple_cmd(node->right, process, msh);
	}
}

/**
 * @brief 実行処理：パイプライン（"|"）
 *
 * @param node
 * @param msh
 */
void	exec_pipeline(t_ast_node *node, t_process process, t_shell *msh)
{
	process.pipe = pipe_init();
	if (node->type & NODE_COMMAND)
	{
		exec_simple_cmd(node, process, msh);
	}
	else
		exec_pipeline_recursive(node, process, msh, STDIN_FILENO);
	wait_child_process();
}