/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:14:45 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/11 20:18:28 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prompt.c
 * @brief コマンド入力状態で使用するプロンプトの生成
 * @date 2023-01-01
 */

#include "terminal.h"
#include "constant.h"
#include "ft_printf.h"
#include "ft_snprintf.h"

/**
 * @brief 初回起動時のバナーを出力する。
 *
 */
void	put_banner(void)
{
	if (DEBUG)
		ft_printf("%s%s%s\n", RED, BANNER_DEV, DEFAULT);
	else
		ft_printf("%s\n", BANNER);
}

/**
 * @brief プロンプト名を生成する
 * @details　プロンプト名の文字列を動的に生成する。
 * 生成した文字列はエラーに使用するめ、プログラムを通してshell構造体に保持し続ける。
 * @return char*　生成した文字列
 */
char	*get_prompt(void)
{
	char	*prompt;

	prompt = (char *)ft_xmalloc(sizeof(char) * PROMPT_LEN);
	ft_snprintf(prompt, PROMPT_LEN, "%s%s > %s", GREEN, PROMPT_NAME, DEFAULT);
	return (prompt);
}
