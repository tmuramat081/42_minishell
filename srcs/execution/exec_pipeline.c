#include "execution.h"
#include "libast.h"


void	set_pipeline_process(t_process *process, int pipe_fd[2])
{

	if (pipe(pipe_fd) < 0)
	{
		exit(EXIT_FAILURE);
	}
	process->writer = pipe_fd[1];
	process->reader = pipe_fd[0];
	process->stdin = false;
	process->stdout = true;
}

void	set_pipeline_mid(t_process *process, int pipe_fd[2])
{
	pipe(pipe_fd);
	process->writer = pipe_fd[1];
	process->stdin = true;
	process->stdout = true;
}

void	reset_pipeline_process(t_process *process, int pipe_fd[2])
{
	process->reader = pipe_fd[0];
	close(process->writer);
	process->stdin = true;
	process->stdout = false;
}


/**
 * @brief 実行処理：パイプライン（"|"）
 *
 * @param node
 * @param msh
 */
void	exec_pipeline(t_ast_node *node, t_process process, t_shell *msh)
{
	t_ast_node *next_node;
	int			pipe_fd[2];

	if (node->type & NODE_COMMAND)
	{
		exec_simple_cmd(node, process, msh);
		return ;
	}
	set_pipeline_process(&process, pipe_fd);
	exec_simple_cmd(node->left, process, msh);
	next_node = node->right;
	while (next_node && next_node->type & NODE_PIPELINE)
	{
		close(process.writer);
		set_pipeline_mid(&process, pipe_fd);
		exec_simple_cmd(node->left, process, msh);
		close(process.reader);
		process.reader = pipe_fd[0];
		next_node = next_node->right;
	}
	reset_pipeline_process(&process, pipe_fd);
	exec_simple_cmd(next_node, process, msh);
	close(process.reader);
}