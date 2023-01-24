/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:59:01 by tmuramat          #+#    #+#             */
/*   Updated: 2023/01/22 21:35:41 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

/**
* @file main.c
* @brief main function.
* @author tmuramat
* @date 2022.12.30
*/

/**
 * @brief シェルの管理情報を初期化する
 * @details 環境変数・プロンプト名
 * @return t_shell*
 */
t_shell	*init_minishell(void)
{
	t_shell *msh;

	msh = (t_shell *)ft_xmalloc(sizeof(t_shell));
	msh->envs = init_environ();
	msh->prompt = get_prompt();
	return (msh);
}

/**
 ***************************************************************
 *	function: main
 *
 *  A re-implemention of Linux Bash shell.
 ***************************************************************
*/
int	main(void)
{
	t_shell	*msh;

	msh = init_minishell();
	boot_minishell(msh);
	return (0);
}
