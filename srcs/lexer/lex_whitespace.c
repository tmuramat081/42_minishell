#include "lexer.h"
#include "libft.h"

/** 状態遷移：空白の場合
 * @brief 
 * 
 * @param tokenizer 
 * @return void* 
 */
void	*lex_whitespace(t_tokenizer *tokenizer)
{
	next(tokenizer);
	while (ft_isspace(peek(tokenizer)) == true)
	{
		next(tokenizer);
	}
	emit(tokenizer, TOKEN_NONE);
	return (lex_general);
}
