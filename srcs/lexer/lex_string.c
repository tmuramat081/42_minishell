#include "lexer.h"

void	*lex_string(t_tokenizer *tokenizer)
{
	char next_c;

	next_c = peek(tokenizer);
	if (is_delimiter(next_c) == true)
	{
		emit(tokenizer, TOKEN_STR);
		return (lex_general);
	}
	next(tokenizer);
	return (lex_string);
}