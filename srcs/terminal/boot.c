/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:25:19 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/29 23:21:03 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libast.h"

/**
 * @brief 起動時バナーの表示（仮）
 *
 */
void	put_banner(void)
{
	ft_putendl_fd("DEVELOPMENT TEST", 1);
}

/** コマンド入力を待機 */
void	boot_minishell(char **envp)
{
	char		*line;
	t_vector	*tokens;
	t_ast		*ast;

	(void)envp;
	put_banner();
	line = NULL;
	ignore_signal();
	while (42)
	{
		line = readline("> ");
		add_history(line);
		tokens = lexer(line);
		ast = parser(tokens, NULL);
		free(line);
	}
}
