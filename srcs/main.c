/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:59:01 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/30 16:33:03 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* @file main.c
* @brief main function.
* @author tmuramat
* @date 2022.12.30
*/

/**
 * @brief Initialize structure
 *
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
