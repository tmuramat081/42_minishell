#include "lexer.h"

void	*lex_eof(t_tokenizer *tokenizer)
{
	puts("EOF");
	next(tokenizer);
	emit(tokenizer, TOKEN_NULL);
	return (NULL);
}