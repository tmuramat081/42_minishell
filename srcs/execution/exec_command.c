/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:06:28 by event             #+#    #+#             */
/*   Updated: 2023/02/06 23:42:23 by kkohki           ###   ########.fr       */
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
	argv = (char **)ft_xmalloc(sizeof(t_ast_node) * (argc + 1));
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

/**
 * @brief コマンド実行プロセスを初期化する。
 *
 * @details 引数・リダイレクト・パイプの設定を行う。
 * @param command
 * @return t_process*
 */
static void	set_command_process(t_process *process, t_command *command)
{
	process->argv = init_arguments(command->arguments);
	process->redirects = command->redirects;
}

/**
 * @brief 実行処理:コマンド
 *
 * @param node
 * @param msh
 */
void	exec_simple_cmd(t_ast_node *node, t_process process, \
			t_shell *msh, t_pipe pipe)
{
	pid_t			pid;
	t_builtin_fn	builtin_command;

	if (!node)
		return ;
	set_command_process(&process, node->command);
	builtin_command = search_builtin(process.argv[0]);
	if (builtin_command && process.is_solo == true)
		pid = 0;
	else
		pid = create_child_process();
	if (pid == 0)
	{
		set_signal(SIGQUIT, SIG_DFL);
		set_pipeline(pipe);
		if (ast_count_redirects(process.redirects) > 0)
			set_redirection(process);
		if (builtin_command)
			exec_internal_command(builtin_command, process, msh);
		else
			exec_external_command(process, msh);
	}
	ft_free_matrix(&process.argv);
}
