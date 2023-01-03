#include "lexer.h"

void	*lex_quote(t_tokenizer *tokenizer)
{
	puts("QUOTE");
	char quote_c;
	char next_c;

	quote_c = next(tokenizer);
	while (true)
	{
		next_c = next(tokenizer);
		if (next_c == '\0')
			return (lex_error);
		else if (next_c == quote_c)
			break ;
	}
	emit(tokenizer, TOKEN_QUOTED_STR);
	return (lex_general);
}
