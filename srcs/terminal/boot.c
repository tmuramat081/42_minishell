/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:25:19 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/25 14:56:20 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	line = NULL;
	ignore_signal();
	while (42)
	{
		line = readline("> ");
		add_history(line);
		tokens = tokenizer(line);
		parser(tokens, NULL);
		free(line);
	}
}
