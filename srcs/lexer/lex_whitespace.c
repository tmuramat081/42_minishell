/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_whitespace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:10:01 by event             #+#    #+#             */
/*   Updated: 2023/02/02 05:10:40 by tmuramat         ###   ########.fr       */
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
