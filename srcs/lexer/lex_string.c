/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:09:42 by event             #+#    #+#             */
/*   Updated: 2023/02/04 13:29:13 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief 状態遷移：文字列の場合
 *
 * @param tokenizer
 * @return void*
 */
void	*lex_string(t_tokenizer *tokenizer)
{
	char	next_c;

	next_c = token_peek(tokenizer);
	if (is_delimiter(next_c) == true)
	{
		token_emit(tokenizer, TOKEN_STR);
		return (lex_general);
	}
	token_next(tokenizer);
	return (lex_string);
}
