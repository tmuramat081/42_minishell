/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:05:09 by event             #+#    #+#             */
/*   Updated: 2023/02/01 23:49:17 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static t_token	*format_space(t_token *token)
{
	char	*formatted;

	formatted = ft_strtrim(token->data, " ");
	free(token->data);
	token->data = formatted;
	return (token);
}

/**
 * @brief 切り出したトークンを整形する。
 *
 * @param token
 */
void	format_token(t_token *token)
{
	if (!token || !token->data)
		return ;
	format_space(token);
}
