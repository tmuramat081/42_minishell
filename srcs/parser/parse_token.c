#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

t_ast_node	*parse_token_list(t_vector *, t_token *);

// [empty]
t_ast_node	*parse_token_list2(t_vector *tokens, t_token *curr)
{
	(void)tokens;
	(void)curr;
	return (NULL);
}

// <token> <tokenlist>
t_ast_node	*parse_token_list1(t_vector *tokens, t_token *curr)
{
	t_ast_node	*tokenListNode;
	t_ast_node	*result;
	char		*arg;

	if (!term(tokens, TOKEN_STR, &curr, &arg))
	    return (NULL);
	tokenListNode = parse_token_list(tokens, curr);
	result = malloc(sizeof(*result));
	ast_node_set_type(result, NODE_ARGUMENT);
	ast_node_set_data(result, arg);
	ast_attach_binary_branch(result, NULL, tokenListNode);
	return (result);
}

t_ast_node* parse_token_list(t_vector *tokens, t_token *curr)
{
    t_ast_node* node;

	node = parse_token_list1(tokens, curr);
	if (curr && node)
        return (node);
	node = parse_token_list2(tokens, curr);
	if (curr && node)
		return (node);
    return (NULL);
}

