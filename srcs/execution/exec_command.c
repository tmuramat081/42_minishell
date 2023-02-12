/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:06:28 by event             #+#    #+#             */
/*   Updated: 2023/02/13 01:58:45 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "execution.h"
#include "libast.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief　コマンド引数のリストを文字列の配列に変換する。
 *
 * @details ast_count_nodesで引数の数を数える
 * @param node
 * @param msh
 * @return char** コマンド引数の配列（[0]にはコマンド名が入る）
 */
static char	**init_arguments(t_argument *arguments)
{
	char	**argv;
	size_t	i;
	size_t	argc;

	argc = ast_count_arguments(arguments);
	argv = (char **)ft_xmalloc(sizeof(char *) * (argc + 1));
	i = 0;
	while (arguments)
	{
		if (*arguments->argument)
			argv[i++] = ft_strdup(arguments->argument);
		arguments = arguments->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	backup_default_fds(int *fd)
{
	fd[0] = xdup(STDIN_FILENO);
	fd[1] = xdup(STDOUT_FILENO);
}

void	exec_cmd_as_parent(t_process process, t_shell *msh, t_builtin_fn bi_cmd)
{
	int	tmp_fds[2];

	msh->is_child_process = false;
	backup_default_fds(tmp_fds);
	set_redirection(process, msh);
	if (errno)
	{
		dup_and_close(tmp_fds[0], STDIN_FILENO);
		dup_and_close(tmp_fds[1], STDOUT_FILENO);
		return ;
	}
	exec_internal_command(bi_cmd, process, msh);
	dup_and_close(tmp_fds[0], STDIN_FILENO);
	dup_and_close(tmp_fds[1], STDOUT_FILENO);
}

void	exec_cmd_as_child(t_process process, t_shell *msh, \
	t_builtin_fn bltin_cmd)
{
	pid_t		pid;
	extern int	g_status;

	msh->is_child_process = true;
	pid = create_child_process();
	if (pid == 0)
	{
		reset_signals();
		set_pipeline(process.pipes);
		set_redirection(process, msh);
		if (bltin_cmd)
			exec_internal_command(bltin_cmd, process, msh);
		else
			exec_external_command(process, msh);
		delete_pipeline(process.pipes);
	}
}

/**
 * @brief 実行処理:コマンド
 *
 * @param node
 * @param msh
 */
void	exec_simple_cmd(t_ast_node *node, t_process process, t_shell *msh)
{
	t_builtin_fn	builtin_cmd;
	extern int		g_status;

	if (!node)
		return ;
	g_status = 0;
	process.argv = init_arguments(node->command->arguments);
	process.redirects = node->command->redirects;
	builtin_cmd = search_builtin(&process);
	if (builtin_cmd && process.is_solo)
		exec_cmd_as_parent(process, msh, builtin_cmd);
	else
		exec_cmd_as_child(process, msh, builtin_cmd);
	ft_free_matrix(&process.argv);
}
