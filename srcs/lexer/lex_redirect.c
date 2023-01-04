#include "lexer.h"

void *lex_redirect_double(t_tokenizer *tokenizer, char current)
{
	t_token_type	type;
	char			next_c;

	next_c = next(tokenizer);
	if (current == '>' && next_c == '>')
		type = TOKEN_RDIR_APPEND;
	else if (current == '<' && next_c == '<')
		type = TOKEN_RDIR_HEREDOC;
	else
		type = TOKEN_NONE;
	emit(tokenizer, type);
	return (lex_general);
}

void	*lex_redirect(t_tokenizer *tokenizer)
{
	t_token_type 	type;
	char			current;

	current = next(tokenizer);
	if (is_redirection(peek(tokenizer)) == true)
		lex_redirect_double(tokenizer, current);
	if (current == '<')
		type = TOKEN_RDIR_INPUT;
	else if (current == '>')
		type = TOKEN_RDIR_OUTPUT;
	else
		type = TOKEN_NONE;
	emit(tokenizer, type);
	return (lex_general);
}
