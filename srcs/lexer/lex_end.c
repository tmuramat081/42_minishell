#include "lexer.h"

#include "lexer.h"

void	*lex_error(t_tokenizer *tokenizer)
{
	(void)tokenizer;
	return (NULL);
}

void	*lex_eof(t_tokenizer *tokenizer)
{
	next(tokenizer);
	emit(tokenizer, TOKEN_END);
	return (NULL);
}