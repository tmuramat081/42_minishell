/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:25:19 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/02 15:01:42 by kkohki           ###   ########.fr       */
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

#include "terminal.h"
#include "libast.h"
#include "constant.h"
#include "parser.h"
#include "expansion.h"
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>

int g_status = 0;

void	delete_token(void *p_token, void *p_item)
{
	t_token	*token;

	(void)p_item;
	token = (t_token *)p_token;
	free(token->data);
}

/**
 * @brief 入力・字句解析・構文解析に使ったメモリを解放する
 *
 * @param line
 * @param lexed_tokens
 * @param syntax_tree
 */
static void	free_buffers(char *line, t_vector *lexed_tokens, t_ast_node *syntax_tree)
{
	ft_vector_foreach(lexed_tokens, delete_token, NULL);
	ft_vector_delete(&lexed_tokens);
	ast_node_delete(syntax_tree);
	free(line);
}

/** コマンド入力の待機 */
void	boot_minishell(t_shell	*msh)
{
	char		*line;
	t_vector	*lexed_tokens;
	t_ast_node	*syntax_tree;

	line = NULL;
	while (true)
	{
		line = readline(msh->prompt);
		if (!line)
			break ;
		else if (*line)
			add_history(line);
		lexer(line, &lexed_tokens);
		parser(lexed_tokens, &syntax_tree, msh);
		expander(syntax_tree, msh);
		executor(syntax_tree, msh);
		free_buffers(line, lexed_tokens, syntax_tree);
	}
	exit(EXIT_FAILURE);
}

/**
 * @brief コマンド入力の待機（デバッグ用）
 *
 * @param msh
 */
void	boot_minishell_dev(t_shell	*msh)
{
	char		*line;
	t_vector	*lexed_tokens;
	t_ast_node	*syntax_tree;

	line = NULL;
	while (true)
	{
		line = readline(msh->prompt);
		if (!line)
			break ;
		else if (*line)
			add_history(line);
		print_input(line);
		lexer(line, &lexed_tokens);
		print_tokens(lexed_tokens);
		parser(lexed_tokens, &syntax_tree, msh);
		print_nodes(syntax_tree);
		expander(syntax_tree, msh);
		print_commands(syntax_tree);
		print_output();
		executor(syntax_tree, msh);
		free_buffers(line, lexed_tokens, syntax_tree);
	}
	exit(EXIT_FAILURE);
}
