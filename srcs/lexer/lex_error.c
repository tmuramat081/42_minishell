#include "lexer.h"

void	*lex_error(t_tokenizer *tokenizer)
{
	puts("ERROR");
	(void)tokenizer;
	return (NULL);
}