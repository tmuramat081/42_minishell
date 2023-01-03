#include "lexer.h"
#include "libft.h"

void	*lex_general(t_tokenizer *tokenizer)
{
	char next_c;

	next_c = peek(tokenizer);
	if (ft_isspace(next_c) == true)
	{
		return (lex_whitespace);
	}
	else if (ft_isnull(next_c) == true)
	{
		return (lex_eof);
	}
	else if (ft_isquote(next_c) == true)
	{
		return (lex_quote);
	}
	else if (is_redirection(next_c) == true)
	{
		return (lex_redirect);
	}
	else if (is_delimiter(next_c) == true)
	{
		return (lex_delimiter);
	}
	else
	{
		return (lex_string);
	}
	emit(tokenizer, TOKEN_NONE);
	return (NULL);
}
