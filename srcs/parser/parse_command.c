#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

/**
 * @brie　コマンドの構文解析
 *
 * @return t_ast_node*
 */

t_ast_node	*parse_command(t_vector *, t_token **);

// <pathname>
t_ast_node	*parse_command2(t_vector *tokens, t_token **curr)
{
	(void)tokens;
	(void)curr;
	return (NULL);
}

// <pathname> <arguments>
t_ast_node	*parse_command1(t_vector *tokens, t_token **curr)
{
	t_ast_node	*rhs_node;
	t_ast_node	*node;
	char		*pathname;

	if (!consume_token(tokens, TOKEN_STR, curr, &pathname))
		return (NULL);
	rhs_node = parse_argument(tokens, curr);
	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set_type(node, NODE_COMMAND);
	ast_node_set_data(node, pathname);
	ast_attach_binary_branch(node, NULL, rhs_node);
	return (node);
}

/**
 * @brief コマンドの解析
 *
 * @param tokens
 * @param curr
 * @return t_ast_node*
 */
t_ast_node	*parse_command(t_vector *tokens, t_token **curr)
{
	t_ast_node	*node;
	t_token		*save;

	save = *curr;
	*curr = save;
	node = parse_command1(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_command2(tokens, curr);
	if (node)
		return (node);
	return (NULL);
}