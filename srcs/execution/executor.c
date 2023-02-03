/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:25:52 by event             #+#    #+#             */
/*   Updated: 2023/02/02 04:20:12 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file execute.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 抽象構文木を操作し実行処理に渡す
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
	t_process	process;

	if (!syntax_tree)
		return ;
	process = (t_process){};
	exec_command_line(syntax_tree, process, msh);
}