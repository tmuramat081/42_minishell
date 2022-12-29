#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

bool term(t_vector *tokens, t_token_type toketype, t_token **curr, char **buff)
{
	if (!curr || !*curr)
		return (false);
    if ((*curr)->type == toketype)
    {
		if (buff)
			*buff = ft_strdup((*curr)->data);
		*curr = (t_token *)ft_vector_next(tokens, *curr, 1);;
        return (true);
    }
	*curr = (t_token *)ft_vector_next(tokens, *curr, 1);;
    return (false);
}

t_ast	*parser(t_vector *tokens, t_shell *msh)
{
	t_ast	*syntax_tree;
	t_token	*curr_token;

	(void)msh;
	curr_token = ft_vector_front(tokens);
	syntax_tree = ast_init();
	syntax_tree->ast = parse_command_line(tokens, curr_token);
	if (DEBUG)
		print_nodes(syntax_tree);
	return (syntax_tree);
}
