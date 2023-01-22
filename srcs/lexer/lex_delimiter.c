#include "lexer.h"
#include "terminal.h"

/**
 * @brief 状態遷移：その他区切り文字の場合
 *
 * @param tokenizer
 * @return void*
 */
void	*lex_delimiter(t_tokenizer *tokenizer)
{
	char 			current;
	t_token_type 	type;

	current = next(tokenizer);
	if (current == '|')
		type = TOKEN_PIPELINE;
	else if (current == ';')
		type = TOKEN_SEMICOLON;
	else
		type = TOKEN_NONE;
	emit(tokenizer, type);
	return (lex_general);
}
