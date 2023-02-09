/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:02:45 by event             #+#    #+#             */
/*   Updated: 2023/02/10 06:18:51 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libast.h"
#include <signal.h>

#define Close(FD) do {                                  \
    int Close_fd = (FD);                                \
    if (close(Close_fd) == -1) {                        \
      perror("close");                                  \
      fprintf(stderr, "%s:%d: close(" #FD ") %d\n",     \
              __FILE__, __LINE__, Close_fd);            \
    }                                                   \
  }while(0)

/**
 * @brief パイプ間のコマンドを順に実行する。
 * @param node
 * @param process
 * @param msh
 * @param pipe
 */
void	_do_pipes(t_ast_node *node, t_process process, t_shell *msh)
{
	t_pipe	pipe;

	pipe.in_fd = STDIN_FILENO;
	while (node->right)
	{
		pipe_update(&pipe);
		pipe.state = PIPE_STDIN | PIPE_STDOUT;
		exec_simple_cmd(node->left, process, msh, pipe);
		Close(pipe.writer);
		Close(pipe.in_fd);
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
	int		backup;

	cnt = ast_count_pipeline(node);
	if (cnt <= 1)
		process.is_solo = true;
	backup = dup(STDIN_FILENO);
	_do_pipes(node, process, msh);
	wait_all_child_processes(cnt);
	xdup2(backup, STDIN_FILENO);
}
