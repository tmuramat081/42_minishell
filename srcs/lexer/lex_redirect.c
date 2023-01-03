#include "lexer.h"

void	*lex_redirect(t_tokenizer *tokenizer)
{
	t_token_type 	type;
	char			current;

	current = next(tokenizer);
	if (current == peek(tokenizer))
	{
		if (current == '<')
			type = TOKEN_RDIR_HEREDOC;
		else if (current == '>')
			type = TOKEN_RDIR_APPEND;
		else
			type = TOKEN_NONE;
	}
	else
	{
		if (current == '<')
			type = TOKEN_RDIR_INPUT;
		else if (current == '>')
			type = TOKEN_RDIR_OUTPUT;
		else
			type = TOKEN_NONE;
	}
	emit(tokenizer, type);
	return (lex_general);
}
