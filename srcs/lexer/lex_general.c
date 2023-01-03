#include "lexer.h"
#include "libft.h"

void	*lex_general(t_tokenizer *tokenizer)
{
	printf("GENERAL\n");
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
	else
	{
		return (lex_string);
	}
	emit(tokenizer, TOKEN_NULL);
	return (NULL);
}
