/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:09:42 by event             #+#    #+#             */
/*   Updated: 2023/01/17 19:09:43 by event            ###   ########.fr       */
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

	next_c = peek(tokenizer);
	if (is_delimiter(next_c) == true)
	{
		emit(tokenizer, TOKEN_STR_PLAIN);
		return (lex_general);
	}
	next(tokenizer);
	return (lex_string);
}
