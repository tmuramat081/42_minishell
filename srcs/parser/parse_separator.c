/**
 * @file parse_separator.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 構文解析その1：セミコロン ";"
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "minishell.h"
#include "parser.h"

// <pipeline>
static t_ast_node	*parse_separator3(t_vector *tokens, t_token **curr)
{
	return (parse_pipeline(tokens, curr));
}

// <pipeline> ';'
t_ast_node	*parse_separator2(t_vector *tokens, t_token **curr)
{
    t_ast_node	*lhs_node;
    t_ast_node	*node;
	char		*semicolon;

    lhs_node = parse_pipeline(tokens, curr);
	if (!lhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_SEMICOLON, curr, &semicolon))
	{
		ast_node_delete(lhs_node);
		return (NULL);
	}
	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set(node, NODE_SEQUENCE, semicolon);
	ast_node_create(node, lhs_node, NULL);
	return (node);
}

// <pipeline> ';' <command_line>
static t_ast_node	*parse_separator1(t_vector *tokens, t_token **curr)
{
	t_ast_node	*lhs_node;
	t_ast_node	*rhs_node;
	t_ast_node	*node;
	char		*semicolon;

	lhs_node = parse_pipeline(tokens, curr);
	if (!lhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_SEMICOLON, curr, &semicolon))
	{
		ast_node_delete(lhs_node);
		return (NULL);
	}
	rhs_node = parse_separator(tokens, curr);
	if (!rhs_node)
	{
		ast_node_delete(rhs_node);
		return (NULL);
	}
 	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set(node, NODE_SEQUENCE, semicolon);
	ast_node_create(node, lhs_node, rhs_node);
	return (node);
}

/**
 * @brief セパレーター（";"）の解析
 *
 * @param tokens
 * @param curr
 * @return t_ast_node*
 */
t_ast_node	*parse_separator(t_vector *tokens, t_token **curr)
{
	t_token		*save;
	t_ast_node	*node;

	save = *curr;
	*curr = save;
	node = parse_separator1(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_separator2(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_separator3(tokens, curr);
	if (node)
		return (node);
	return (NULL);
}
