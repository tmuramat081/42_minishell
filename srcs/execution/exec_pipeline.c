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

void delete_zombie_process(void)
{
	int		status;

    while (waitpid(-1, &status, 0) <= 0);
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
	while (node && (node->type & NODE_PIPELINE))
	{
		pipe_create(&process.pipe);
		process.pipe.state = PIPE_STDOUT;
		exec_simple_cmd(node->left, process, msh);
		process.pipe.state |= PIPE_STDIN;
		dup2(process.pipe.reader, STDIN_FILENO);
		close(process.pipe.writer);
		node = node->right;
	}
	process.pipe.state = PIPE_STDIN;
	exec_simple_cmd(node, process, msh);
	delete_zombie_process();
}