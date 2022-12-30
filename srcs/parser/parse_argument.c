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
	ast_node_set_type(node, NODE_ARGUMENT);
	ast_node_set_data(node, arg);
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
	t_ast_node* node;

	node = parse_argument1(tokens, curr);
	if (node)
		return (node);
	node = parse_argument2(tokens, curr);
	if (node)
		return (node);
	return (NULL);
}

