/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:02:45 by event             #+#    #+#             */
/*   Updated: 2023/02/08 00:41:10 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libast.h"
#include <signal.h>

/**
 * @brief パイプ間のコマンドを再帰的に実行する。
 * @param node
 * @param process
 * @param msh
 * @param pipe
 */
void	exec_pipeline_recursive(t_ast_node *node, t_process process, \
			t_shell *msh, t_pipe pipe)
{
	if (node->type & NODE_COMMAND)
	{
		pipe.state = PIPE_STDIN;
		exec_simple_cmd(node, process, msh, pipe);
	}
	else
	{
		pipe_update(&pipe);
		pipe.state = PIPE_STDIN | PIPE_STDOUT;
		exec_simple_cmd(node->left, process, msh, pipe);
		close_file(pipe.writer);
		close_file(pipe.in_fd);
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
	t_pipe	pipe;

	process.is_solo = false;
	if (ast_count_pipeline(node) <= 1)
		process.is_solo = true;
	pipe = pipe_init();
	pipe_fd_backup(&pipe);
	exec_pipeline_recursive(node, process, msh, pipe);
	wait_all_child_processes();
	pipe_fd_restore(pipe);
}
