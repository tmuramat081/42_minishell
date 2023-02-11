/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:25:52 by event             #+#    #+#             */
/*   Updated: 2023/02/11 19:09:19 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file execute.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 抽象構文木をトップダウンで走査し、コマンドの実行処理を行う
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "libast.h"
#include "parser.h"
#include "terminal.h"
#include "execution.h"

/**
 * @brief コマンド実行のエントリーポイント
 *
 * @param syntax_tree 抽象構文木
 * @param msh
 */
void	executor(t_ast_node *syntax_tree, t_shell *msh)
{
	extern int	g_status;
	t_process	process;

	g_status = 0;
	if (!syntax_tree)
		return ;
	process = (t_process){};
	exec_command_line(syntax_tree, process, msh);
}
