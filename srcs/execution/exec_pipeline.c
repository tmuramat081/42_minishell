/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:02:45 by event             #+#    #+#             */
/*   Updated: 2023/02/11 02:31:42 by tmuramat         ###   ########.fr       */
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
void	_do_pipes(t_ast_node *node, t_process process, t_shell *msh, t_pipe *pipes)
{
	pipes->state = PIPE_STDOUT;
	while (node->right)
	{
		exec_simple_cmd(node->left, process, msh, pipes);
		pipes->state |= PIPE_STDIN;
		pipes->idx += 2;
		node = node->right;
	}
	pipes->state = PIPE_STDIN;
	exec_simple_cmd(node, process, msh, pipes);
}
/**
 * @brief 実行処理：パイプライン（"|"）
 *
 * @param node
 * @param msh
 */
void	exec_pipeline(t_ast_node *node, t_process process, t_shell *msh)
{
	size_t		cnt;
	t_pipe		*pipes;

	cnt = ast_count_pipeline(node);
	if (cnt <= 1)
		process.is_solo = true;
	pipes = init_pipeline(cnt);
	_do_pipes(node, process, msh, pipes);
	delete_pipeline(pipes);
	wait_all_child_processes(cnt);
}
