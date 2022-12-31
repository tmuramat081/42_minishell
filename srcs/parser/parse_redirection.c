#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

/**
* @file parse_redirection.c
* @brief 構文解析その3：リダイレクト">">>"<"<<"
* @author tmuramat
* @date 2022.12.30
*/

// <command>
static t_ast_node *parse_redirection3(t_vector *tokens, t_token **curr)
{
	t_ast_node *node;

	node = parse_command(tokens, curr);
	return (node);
}

// <command> '>' <filename>
static t_ast_node	*parse_redirection2(t_vector *tokens, t_token **curr)
{
    t_ast_node	*rhs_node;
    t_ast_node	*result;
	char		*filename;

    rhs_node = parse_command(tokens, curr);
	if (!rhs_node)
        return (NULL);
    if (!consume_token(tokens, TOKEN_RDIR, curr, NULL))
	{
		ast_node_delete(rhs_node);
		return (NULL);
	}
	if (!consume_token(tokens, TOKEN_STR, curr, &filename))
	{
		free(filename);
        ast_node_delete(rhs_node);
        return (NULL);
    }
    result = ft_xmalloc(sizeof(t_ast_node));
    ast_node_set_type(result, NODE_REDIRECT_IN);
    ast_node_set_data(result, filename);
    ast_attach_binary_branch(result, NULL, rhs_node);
	return (result);
}

// <command> '<' <filename>
static t_ast_node	*parse_redirection1(t_vector *tokens, t_token **curr)
{
	t_ast_node	*rhs_node;
	t_ast_node	*result;
	char		*filename;

	rhs_node = parse_command(tokens, curr);
	if (!rhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_LDIR, curr, NULL))
	{
		ast_node_delete(rhs_node);
		return (NULL);
	}
	if (!consume_token(tokens, TOKEN_STR, curr, &filename))
	{
		free(filename);
		ast_node_delete(rhs_node);
		return (NULL);
	}
	result = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set_type(result, NODE_REDIRECT_IN);
	ast_node_set_data(result, filename);
	ast_attach_binary_branch(result, NULL, rhs_node);
	return (result);
}

/**
 * @brief  リダイレクトの解析
 *
 * @param tokens
 * @param curr
 * @return t_ast_node*
 */
t_ast_node	*parse_redirection(t_vector *tokens, t_token **curr)
{
	t_token		*save;
	t_ast_node* node;

	save = *curr;
	node = parse_redirection1(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_redirection2(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_redirection3(tokens, curr);
	if (node)
		return (node);
	return (NULL);
}

