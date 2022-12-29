#include "minishell.h"
#include "lexer.h"
#include "parser.h"

char *convert_type_to_str(t_token_type type)
{
	if (type == TOKEN_STR)
		return ("STRING");
	if (type == TOKEN_RDIR)
		return (">");
	if (type == TOKEN_RRDIR)
		return (">>");
	if (type == TOKEN_LDIR)
		return ("<");
	if (type == TOKEN_LLDIR)
		return ("<<");
	if (type == TOKEN_SPACE)
		return (" ");
	if (type == TOKEN_PIPELINE)
		return ("|");
	if (type == TOKEN_AMPERSAND)
		return ("&");
	if (type == TOKEN_SEMICOLON)
		return (";");
	if (type == TOKEN_NULL)
		return ("[EOL]");
	return ("NONE");
}


void	print_token(void *p_str, void *p_index)
{
	t_token *token;
	int		*index;
	char	*type;

	index = p_index;
	token = p_str;
	type = convert_type_to_str(token->type);
	ft_printf("[%*d] %*s %*s\n", 2, *index, 20, token->data, 20, type);
	(*index)++;
}

void	print_tokens(t_vector *tokens)
{
	int	index;

	index = 0;
	ft_printf("============================\n");
	ft_printf("%s %*s %*s\n", "No. ", 20, "command", 20, "type");
	ft_printf("----------------------------\n");
	ft_vector_foreach(tokens, print_token, &index);
	ft_printf("============================\n");
}