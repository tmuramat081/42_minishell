#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

t_ast_node* parse_simple_command(t_vector *, t_token *);

// <pathname> <tokenlist>
t_ast_node* parse_simple_command1(t_vector *tokens, t_token *curr)
{
    t_ast_node	*tokenListNode;
    t_ast_node	*result;
    char		*pathname;

	printf("%s\n", curr->data);
    if (!term(tokens, TOKEN_STR, &curr, &pathname))
        return (NULL);
	printf("%s\n", curr->data);
    tokenListNode = parse_token_list(tokens, curr);
    result = ft_xmalloc(sizeof(*result));
    ast_node_set_type(result, NODE_CMDPATH);
    ast_node_set_data(result, pathname);
	ast_attach_binary_branch(result, NULL, tokenListNode);
    return (result);
}

t_ast_node* parse_simple_command(t_vector *tokens, t_token *curr)
{
//	puts("simple command");
	return (parse_simple_command1(tokens, curr));
}