#include "lexer.h"
#include "libft.h"

static bool	ft_isquote(int c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

static bool	ft_isnull(int c)
{
	if (c == '\0')
		return(true);
	return (false);
}

bool	is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_delimiter(int c)
{
	if (ft_isspace(c) || ft_isquote(c) || ft_isnull(c)
		|| is_redirection(c) || c == '|' || c == ';')
		return (true);
	return (false);
}

/**
 * @brief 状態遷移：通常（ここから各状態に遷移する）。
 *
 * @param tokenizer 
 * @return void* 
 */
void	*lex_general(t_tokenizer *tokenizer)
{
	char next_c;

	next_c = peek(tokenizer);
	if (ft_isspace(next_c) == true)
		return (lex_whitespace);
	else if (ft_isnull(next_c) == true)
		return (lex_eof);
	else if (ft_isquote(next_c) == true)
		return (lex_quote);
	else if (is_redirection(next_c) == true)
		return (lex_redirect);
	else if (is_delimiter(next_c) == true)
		return (lex_delimiter);
	else
		return (lex_string);
	emit(tokenizer, TOKEN_NONE);
	return (NULL);
}
