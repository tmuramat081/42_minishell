#include "lexer.h"
#include "libft.h"

static t_token	*format_space(t_token *token)
{
	char *formatted;

	formatted = ft_strtrim(token->data, " ");
	free(token->data);
	token->data = formatted;
	return (token);
}

static t_token *format_quote(t_token *token)
{
	char	*formatted;

	if (token->type == TOKEN_STR_SQUOTE)
		formatted = ft_strtrim(token->data, "\'");
	else if (token->type == TOKEN_STR_DQUOTE)
		formatted = ft_strtrim(token->data, "\"");
	else
		formatted = ft_strdup(token->data);
	free(token->data);
	token->data = formatted;
	return (token);
}

/**
 * @brief 切り出したトークンを整形する。
 * 
 * @param token 
 */
void	format_token(t_token *token)
{
	format_space(token);
	format_quote(token);
}