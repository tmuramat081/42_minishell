/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:16:55 by event             #+#    #+#             */
/*   Updated: 2023/01/17 19:16:58 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 構文解析のエントリーポイント
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

/**		Backus-Naur Form (BNF)
 *
	<command_line>	::= <pipeline> ';' <command_line>
					|	<pipeline> ';'
					|	<pipeline>

	<pipeline>		::=	<simple_cmd> '|' <pipeline>
					|	<simple_cmd>

	<simple_cmd>	::= cmd_name
					|	cmd_name <cmd_suffix>

	<cmd_suffix>	::= 			 <io_redirect>
					|	<cmd_suffix> <io_redirect>
					|				 word
					|	<cmd_suffix> word

	<io_redirect>	::= '>'  filename
					| 	'>>' filename
					| 	'<'  filename
					| 	'<<' here_end
 *
**/

/**
 * @brief 再帰下降パーサーにより抽象構文木を作成する
 *
 * @param tokens lexerにより分解された各単語
 * @param msh shellのステータスを管理する構造体
 * @return t_ast* 抽象構文木
 */
t_ast_node	*parser(t_vector *tokens, t_shell *msh)
{
	t_ast_node	*syntax_tree;
	t_token		*curr_token;

	(void)msh;
	curr_token = ft_vector_front(tokens);
	syntax_tree = parse_command_line(tokens, &curr_token);
	return (syntax_tree);
}
