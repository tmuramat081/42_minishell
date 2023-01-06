#include "lexer.h"

/**
 * @brief 状態遷移：クオーテーションの場合
 * 
 * @param tokenizer 
 * @return void* 
 */
void	*lex_quote(t_tokenizer *tokenizer)
{
	char quote_c;
	char tmp_c;

	quote_c = next(tokenizer);
	while (true)
	{
		tmp_c = next(tokenizer);
		if (tmp_c == '\0')
			return (lex_error);
		else if (tmp_c == quote_c)
			break ;
	}
	if (quote_c == '\'')
		emit(tokenizer, TOKEN_STR_SQUOTE);
	else if (quote_c == '"')
		emit(tokenizer, TOKEN_STR_DQUOTE);
	return (lex_general);
}
