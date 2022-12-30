/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:25:19 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/30 08:25:54 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libast.h"
#include "ft_snprintf.h"
#include "constant.h"

/*６ｙｙ
* @file boot.c
* @brief コマンドラインの待機状態
* @author tmuramat
* @date 2022.12.30
*/

/**
 * @brief 起動時バナーを表示する
 *
 */
void	put_banner(void)
{
	ft_putendl_fd("DEVELOPMENT TEST", 1);
}

/** コマンド入力を待機 */
void	boot_minishell(t_shell	*msh)
{
	char		*line;
	t_vector	*tokens;
	t_ast		*ast;

	line = NULL;
	ignore_signal();
	put_banner();
	while (47)
	{
		line = readline(msh->prompt);
		add_history(line);
		tokens = lexer(line);
		ast = parser(tokens, msh);
		free(line);
	}
}
