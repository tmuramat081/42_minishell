#include "minishell.h"
#include "parser.h"

// <job>
static t_ast_node	*parse_command_line3(t_vector *tokens, t_token *curr)
{
	return parse_pipe(tokens, curr);
}

// <job> ';'
t_ast_node	*parse_command_line2(t_vector *tokens, t_token *curr)
{
    t_ast_node	*jobNode;
    t_ast_node	*result;

    if ((jobNode = parse_pipe(tokens, curr)) == NULL)
        return NULL;

	if (!term(tokens, TOKEN_SEMICOLON, &curr, NULL))
	{
	    ast_node_delete(jobNode);
	    return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_node_set_type(result, NODE_SEQ);
	ast_attach_binary_branch(result, jobNode, NULL);
    return (result);
}

// <job> ';' <command_line>
static t_ast_node	*parse_command_line1(t_vector *tokens, t_token *curr)
{
	t_ast_node	*jobNode;
	t_ast_node	*cmdlineNode;
	t_ast_node	*result;

	jobNode = parse_pipe(tokens, curr);
	if (!jobNode)
		return (NULL);
	if (!term(tokens, TOKEN_SEMICOLON, &curr, NULL))
	{
		ast_node_delete(jobNode);
		return (NULL);
	}
	if ((cmdlineNode = parse_command_line(tokens, curr)) == NULL)
	{
		ast_node_delete(jobNode);
		return (NULL);
	}
	result = ft_xmalloc(sizeof(*result));
	ast_node_set_type(result, NODE_SEQ);
	ast_attach_binary_branch(result, jobNode, cmdlineNode);
	return (result);
}

t_ast_node	*parse_command_line(t_vector *tokens, t_token *curr)
{
    t_ast_node	*node;

//	puts("command line");
	node = parse_command_line1(tokens, curr);
	if (curr && node)
		return (node);
	node = parse_command_line2(tokens, curr);
	if (curr && node)
		return (node);
	node = parse_command_line3(tokens, curr);
	if (curr && node)
		return (node);
	return (NULL);
}
