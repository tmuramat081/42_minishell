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
    t_ast_node	*result;

    lhs_node = parse_pipeline(tokens, curr);
	if (!lhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_SEMICOLON, curr, NULL))
	{
		ast_node_delete(lhs_node);
		return (NULL);
	}
	result = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set_type(result, NODE_SEQUENCE);
	ast_attach_binary_branch(result, lhs_node, NULL);
	return (result);
}

// <pipeline> ';' <command_line>
static t_ast_node	*parse_separator1(t_vector *tokens, t_token **curr)
{
	t_ast_node	*lhs_node;
	t_ast_node	*rhs_node;
	t_ast_node	*result;

	lhs_node = parse_pipeline(tokens, curr);
	if (!lhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_SEMICOLON, curr, NULL))
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
	result = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set_type(result, NODE_SEQUENCE);
	ast_attach_binary_branch(result, lhs_node, rhs_node);
	return (result);
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
