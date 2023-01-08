/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:25:19 by tmuramat          #+#    #+#             */
/*   Updated: 2023/01/08 15:33:22 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * @file boot.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief コマンド入力の待機状態
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "minishell.h"
#include "libast.h"
#include "ft_snprintf.h"
#include "constant.h"
#include "ft_printf.h"
#include "parser.h"
#include "execution.h"

/**
 * @brief 起動時バナーを表示する
 *
 */
void	put_banner(void)
{
	if (DEBUG)
		ft_printf("%s%s%s\n", RED, BANNER_DEV, DEFAULT);
	else
		ft_printf("%s\n", BANNER);
}

/** コマンド入力を待機 */
void	boot_minishell(t_shell	*msh)
{
	char		*line;
	t_vector	*lexed_tokens;
	t_ast		*syntax_tree;

	line = NULL;
	ignore_signal();
	put_banner();
	while (true)
	{
		line = readline(msh->prompt);
		if (!line)
			break ;
		else if (*line)
			add_history(line);
		if(DEBUG)
			print_input(line);
		lexer(line, &lexed_tokens);
		if(DEBUG)
			print_tokens(lexed_tokens);
		syntax_tree = parser(lexed_tokens, msh);
		if(DEBUG)
			print_nodes(syntax_tree);
		if(DEBUG)
			print_output();
		execute_syntax_tree(syntax_tree, msh);
		free(line);
	}
	exit(EXIT_FAILURE);
}
