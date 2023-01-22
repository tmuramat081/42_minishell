#include "execution.h"
#include "libast.h"
#include <signal.h>

void	exec_pipeline_recursive(t_ast_node *node, t_process process, t_shell *msh, t_pipe pipe)
{
	if (node->type & NODE_COMMAND)
	{
		pipe.state = PIPE_STDIN;
		exec_simple_cmd(node, process, msh, pipe);
		return ;
	}
	else
	{
		pipe = pipe_create();
		pipe.state = PIPE_STDIN | PIPE_STDOUT;
		exec_simple_cmd(node->left, process, msh, pipe);
		close(pipe.writer);
		close(pipe.in_fd);
		pipe.in_fd = pipe.reader;
		if (node->right)
			exec_pipeline_recursive(node->right, process, msh, pipe);
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
	t_pipe pipe;

	pipe = pipe_init();
	pipe_fd_backup(&pipe);
	exec_pipeline_recursive(node, process, msh, pipe);
	pipe_fd_restore(pipe);
	wait_all_child_processes();
}