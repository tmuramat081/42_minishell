/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:19:13 by event             #+#    #+#             */
/*   Updated: 2023/01/17 19:20:31 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"
#include "ft_deque.h"

/**
 * @brief 解析対象のインデックスを次に進める。
 *
 * @param tokens
 * @param curr
 */
void	next_token(t_vector *tokens, t_token **curr)
{
	*curr = (t_token *)ft_vector_next(tokens, *curr, 1);
}

/**
 * @brief 解析対象の文字を取得し、インデックスを次に進める。
 *
 * @param tokens トークンのリスト
 * @param toketype　判定したいトークンの種別　
 * @param curr　現在解析しているトークン
 * @param buff　正であればbuffにトークンの文字列を書き込む
 * @return true
 * @return false
 */
char	*scan_token(t_vector *tokens, t_token **curr)
{
	char	*buff;

	if (!curr || !*curr || (*curr)->type & TOKEN_END)
		return (NULL);
	buff = ft_strdup((*curr)->data);
	if (!buff)
		return (NULL);
	next_token(tokens, curr);
	return (buff);
}
