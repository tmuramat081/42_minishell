#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

// <simple_command>
t_ast_node *parse_command3(t_vector *tokens, t_token *curr_token)
{
	return parse_simple_command(tokens, curr_token);
}

// <simple_command> '>' <filename>
t_ast_node	*parse_command2(t_vector *tokens, t_token *curr)
{
    t_ast_node	*simplecmdNode;
    t_ast_node	*result;
	char		*filename;

    simplecmdNode = parse_simple_command(tokens, curr);
	if (!simplecmdNode)
        return (NULL);
	puts("-------ok-------");
	printf("%s\n", curr->data);
    if (!term(tokens, TOKEN_RDIR, &curr, NULL))
	{
		ast_node_delete(simplecmdNode);
		return (NULL);
	}
	if (!term(tokens, TOKEN_NONE, &curr, &filename))
	{
		free(filename);
        ast_node_delete(simplecmdNode);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_REDIRECT_IN);
    ast_node_set_data(result, filename);
    ast_attach_binary_branch(result, NULL, simplecmdNode);
	return (result);
}

// <simple_command> '<' <filename>
t_ast_node	*parse_command1(t_vector *tokens, t_token *curr)
{
	t_ast_node	*simplecmdNode;
	t_ast_node	*result;
	char		*filename;

	simplecmdNode = parse_simple_command(tokens, curr);
	if (!simplecmdNode)
		return (NULL);
	if (!term(tokens, TOKEN_LDIR, &curr, NULL))
	{
		ast_node_delete(simplecmdNode);
		return (NULL);
	}
	if (!term(tokens, TOKEN_NONE, &curr, &filename))
	{
		free(filename);
		ast_node_delete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_node_set_type(result, NODE_REDIRECT_IN);
	ast_node_set_data(result, filename);
	ast_attach_binary_branch(result, NULL, simplecmdNode);
	return (result);
}

t_ast_node	*parse_command(t_vector *tokens, t_token *curr)
{
	t_ast_node* node;

	//puts("parse_command");
	node = parse_command1(tokens, curr);
	if (curr && node)
		return (node);
	node = parse_command2(tokens, curr);
	if (curr && node)
		return (node);
	node = parse_command3(tokens, curr);
	if (curr && node)
		return (node);
	return (NULL);
}

