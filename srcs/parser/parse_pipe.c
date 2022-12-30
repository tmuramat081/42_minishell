#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

t_ast_node	*parse_pipe2(t_vector *tokens, t_token *curr_token)
{
    return (parse_command(tokens, curr_token));
}

// <command> '|' <job>
t_ast_node	*parse_pipe1(t_vector *tokens, t_token *curr)
{
    t_ast_node	*cmdNode;
    t_ast_node	*jobNode;
    t_ast_node	*result;

    cmdNode = parse_command(tokens, curr);
	if (!cmdNode)
        return (NULL);
    if (!term(tokens, TOKEN_PIPELINE, &curr, NULL))
	{
        ast_node_delete(cmdNode);
        return (NULL);
    }
    if ((jobNode = parse_pipe(tokens, curr)) == NULL) {
        ast_node_delete(cmdNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_PIPE);
    ast_attach_binary_branch(result, cmdNode, jobNode);

    return result;
}

t_ast_node	*parse_pipe(t_vector *tokens, t_token *curr)
{
    t_ast_node* node;

//	puts("job");
    node = parse_pipe1(tokens, curr);
	if (curr && node)
		return (node);
    node = parse_pipe2(tokens, curr);
	if (curr && node)
		return (node);
	return (NULL);
}

