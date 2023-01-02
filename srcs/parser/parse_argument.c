/**
 * @file parse_argument.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 構文解析その5：引数 ex."-n", "hello"
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

t_ast_node	*parse_argument(t_vector *, t_token **);

// [empty]
t_ast_node	*parse_argument2(t_vector *tokens, t_token **curr)
{
	(void)tokens;
	(void)curr;
	return (NULL);
}

// <arg> <argument>
t_ast_node	*parse_argument1(t_vector *tokens, t_token **curr)
{
	t_ast_node	*rhs_node;
	t_ast_node	*node;
	char		*arg;

	if (!consume_token(tokens, TOKEN_STR, curr, &arg))
		return (NULL);
	rhs_node = parse_argument(tokens, curr);
	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set(node, NODE_ARGUMENT, arg);
	ast_attach_binary_branch(node, NULL, rhs_node);
	return (node);
}

/**
 * @brief コマンド引数の解析
 *
 * @param tokens
 * @param curr
 * @return t_ast_node*
 */
t_ast_node	*parse_argument(t_vector *tokens, t_token **curr)
{
	t_token *save;
	t_ast_node* node;

	save = *curr;
	*curr = save;
	node = parse_argument1(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_argument2(tokens, curr);
	if (node)
		return (node);
	return (NULL);
}

