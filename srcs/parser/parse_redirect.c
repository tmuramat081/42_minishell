/**
 * @file parse_redirection.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 構文解析その3：リダイレクト ">, >>, <, <<"
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "libast.h"
#include "lexer.h"
#include "parser.h"

// <command>
static t_ast_node	*parse_redirect5(t_vector *tokens, t_token **curr)
{
	return (parse_command(tokens, curr));
}


// <command> '<<' 'filename'
static t_ast_node	*parse_redirect4(t_vector *tokens, t_token **curr)
{
	t_ast_node	*node;
	t_ast_node	*rhs_node;
	char		*filename;

	rhs_node = parse_command(tokens, curr);
	if (!rhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_RDIR_HEREDOC, curr, NULL))
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
	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set(node, NODE_RDIR_HEREDOC, filename);
	ast_attach_binary_branch(node, NULL, rhs_node);
	return (node);
}

// <command> '>>' 'filename'
static t_ast_node	*parse_redirect3(t_vector *tokens, t_token **curr)
{
	t_ast_node	*node;
	t_ast_node	*rhs_node;
	char		*filename;

	rhs_node = parse_command(tokens, curr);
	if (!rhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_RDIR_APPEND, curr, NULL))
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
	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set(node, NODE_RDIR_APPEND, filename);
	ast_attach_binary_branch(node, NULL, rhs_node);
	return (node);
}

// <command> '>' 'filename'
static t_ast_node	*parse_redirect2(t_vector *tokens, t_token **curr)
{
	t_ast_node	*node;
	t_ast_node	*rhs_node;
	char		*filename;

	rhs_node = parse_command(tokens, curr);
	if (!rhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_RDIR_OUTPUT, curr, NULL))
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
    node = ft_xmalloc(sizeof(t_ast_node));
    ast_node_set(node, NODE_RDIR_OUTPUT, filename);
    ast_attach_binary_branch(node, NULL, rhs_node);
	return (node);
}

// <command> '<' 'filename'
static t_ast_node	*parse_redirect1(t_vector *tokens, t_token **curr)
{
	t_ast_node	*node;
	t_ast_node	*rhs_node;
	char		*filename;

	rhs_node = parse_command(tokens, curr);
	if (!rhs_node)
		return (NULL);
	if (!consume_token(tokens, TOKEN_RDIR_INPUT, curr, NULL))
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
	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set(node, NODE_RDIR_INPUT, filename);
	ast_attach_binary_branch(node, NULL, rhs_node);
	return (node);
}

/**
 * @brief  リダイレクトの解析
 *
 * @param tokens
 * @param curr
 * @return t_ast_node*
 */
t_ast_node	*parse_redirect(t_vector *tokens, t_token **curr)
{
	t_token		*save;
	t_ast_node* node;

//	puts("REDIRECT");
	save = *curr;
	node = parse_redirect1(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_redirect2(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_redirect3(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_redirect4(tokens, curr);
	if (node)
		return (node);
	*curr = save;
	node = parse_redirect5(tokens, curr);
	if (node)
		return (node);
	return (NULL);
}

