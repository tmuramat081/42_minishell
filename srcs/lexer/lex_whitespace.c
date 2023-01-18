/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_whitespace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:10:01 by event             #+#    #+#             */
/*   Updated: 2023/01/17 19:10:02 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (lex_general);
}
