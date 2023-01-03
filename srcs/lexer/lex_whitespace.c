#include "lexer.h"
#include "libft.h"

void	*lex_whitespace(t_tokenizer *tokenizer)
{
	next(tokenizer);
	while (ft_isspace(peek(tokenizer)) == true)
	{
		next(tokenizer);
	}
	return (lex_general);
}
