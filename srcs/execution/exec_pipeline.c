#include "execution.h"
#include "libast.h"


void	set_pipeline_process(t_process *process)
{

	if (pipe(process->pipe) < 0)
	{
		exit(EXIT_FAILURE);
	}
	process->pipewrite = process->pipe[1];
	process->piperead = process->pipe[0];
}



void	reset_pipeline_process(t_process *process)
{
	process->piperead = process->pipe[0];
	close(process->piperead);
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

	if (node->type & NODE_COMMAND)
	{
		exec_simple_cmd(node, process, msh);
		return ;
	}
	set_pipeline_process(&process);
	exec_simple_cmd(node->left, process, msh);
	next_node = node->right;
	while (next_node && next_node->type & NODE_PIPELINE)
	{
		close(process.pipewrite);
		pipe(process.pipe);
		process.pipewrite = process.pipe[1];
		exec_simple_cmd(node, process, msh);
		close(process.piperead);
		next_node = next_node->right;
	}
	reset_pipeline_process(&process);
	exec_simple_cmd(next_node, process, msh);
	close(process.piperead);
}