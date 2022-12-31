#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

/**
* @file parse_pipeline.c
* @brief 構文解析その2：パイプライン"|"
* @author tmuramat
* @date 2022.12.30
*/

static t_ast_node	*parse_pipeline2(t_vector *tokens, t_token **curr)
{
	t_ast_node *node;

	node = parse_redirection(tokens, curr);
	return (node);
}

// <command> '|' <pipeline>
static t_ast_node	*parse_pipeline1(t_vector *tokens, t_token **curr)
{
	t_ast_node	*lhs_node;
	t_ast_node	*rhs_node;
	t_ast_node	*node;
	char		*pipeline;

	lhs_node = parse_redirection(tokens, curr);
	if (!lhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_PIPELINE, curr, &pipeline))
	{
		ast_node_delete(lhs_node);
		return (NULL);
	}
	rhs_node = parse_pipeline(tokens, curr);
	if (!rhs_node)
	{
		ast_node_delete(lhs_node);
		return (NULL);
	}
	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set_type(node, NODE_PIPELINE);
	ast_node_set_data(node, pipeline);
	ast_attach_binary_branch(node, lhs_node, rhs_node);
	return (node);
}

/**
 * @brief パイプの解析
 *
 * @param tokens
 * @param curr
 * @return t_ast_node*
 */
t_ast_node	*parse_pipeline(t_vector *tokens, t_token **curr)
{
    t_ast_node	*node;
	t_token *save;

	save = *curr;
	*curr = save;
    node = parse_pipeline1(tokens, curr);
	if (node)
		return (node);
	*curr = save;
    node = parse_pipeline2(tokens, curr);
	if (node)
		return (node);
	return (NULL);
}

