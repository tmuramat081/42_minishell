/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:02:45 by event             #+#    #+#             */
/*   Updated: 2023/02/09 05:21:25 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libast.h"
#include <signal.h>

size_t cnt = 0;
/**
 * @brief パイプ間のコマンドを再帰的に実行する。
 * @param node
 * @param process
 * @param msh
 * @param pipe
 */
void	exec_pipeline_recursive(t_ast_node *node, t_process process, t_shell *msh)
{
	t_pipe	pipe;

	pipe = pipe_init();
	while (node->right)
	{
		pipe_update(&pipe);
		pipe.state = PIPE_STDIN | PIPE_STDOUT;
		exec_simple_cmd(node->left, process, msh, pipe);
		close_file(pipe.writer);
		pipe.in_fd = pipe.reader;
		node = node->right;
	}
	pipe.state = PIPE_STDIN;
	exec_simple_cmd(node, process, msh, pipe);
}

/**
 * @brief 実行処理：パイプライン（"|"）
 *
 * @param node
 * @param msh
 */
void	exec_pipeline(t_ast_node *node, t_process process, t_shell *msh)
{
	size_t	cnt;

	process.is_solo = false;
	cnt = ast_count_pipeline(node);
	if (cnt <= 1)
		process.is_solo = true;
	exec_pipeline_recursive(node, process, msh);
	wait_all_child_processes(cnt);
}
