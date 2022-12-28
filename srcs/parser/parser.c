#include "minishell.h"
#include "parser.h"


t_token_type	get_token_type(char *token_value)
{
	if (!ft_strcmp(STR_RDIR, token_value))
		return (TOKEN_RDIR);
	if (!ft_strcmp(STR_RRDIR, token_value))
		return (TOKEN_RRDIR);
	if (!ft_strcmp(STR_LDIR, token_value))
		return (TOKEN_LDIR);
	if (!ft_strcmp(STR_LLDIR, token_value))
		return (TOKEN_LLDIR);
	if (!ft_strcmp(STR_SPACE, token_value))
		return (TOKEN_SPACE);
	if (!ft_strcmp(STR_PIPELINE, token_value))
		return (TOKEN_PIPELINE);
	if (!ft_strcmp(STR_AMPERSAND, token_value))
		return (TOKEN_AMPERSAND);
	if (!ft_strcmp(STR_SEMICOLON, token_value))
		return (TOKEN_SEMICOLON);
	return (TOKEN_STR);
}

void	set_token_types(void *p_token)
{
	t_token	*token;

	token = (t_token *)p_token;
	token->type = get_token_type(token->value);
}

void	parser(t_vector *tokens, t_shell *msh)
{
	ft_vector_foreach(tokens, set_token_types);
}
