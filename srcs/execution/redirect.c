/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:17:55 by event             #+#    #+#             */
/*   Updated: 2023/02/14 00:07:45 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "execution.h"
#include "expansion.h"
#include "parser.h"
#include "libast.h"
#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief ファイルをオープンし、オープンしたfdの値を取得する。
 * @detail heredocの場合は入力処理を呼び出し、入力したfdを取得する。
 * @param redirect_type
 * @return int
 */
static int	open_file(char *filename, t_node_type type)
{
	const int	file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int			fd;

	fd = 0;
	if (type & NODE_RDIR_OUTPUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, file_mode);
	else if (type & NODE_RDIR_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, file_mode);
	else if (type & NODE_RDIR_INPUT)
		fd = open(filename, O_RDONLY);
	else if (type & NODE_RDIR_HEREDOC)
		fd = heredoc_redirect(filename);
	return (fd);
}

/**
 * @brief リダイレクト先の設定を行う。
 * @details 新規にファイルを開き（open）、入力／出力先に指定（dup2）する。
 * @param process
 */
void	set_redirect(t_process process, t_shell *msh)
{
	size_t		i;

	if (!process.redir)
		return ;
	i = 0;
	while (process.redir[i].file)
	{
		process.redir[i].io = open_file(process.redir[i].file, process.redir[i].type);
		if (process.redir[i].io < 0)
		{
			shell_perror(process.redir[i].file, msh, 1);
			return ;
		}
		i++;
	}
}

void	dup_redirect(t_process process, t_shell *msh)
{
	size_t		i;

	(void)msh;
	if (!process.redir)
		return ;
	i = 0;
	while (process.redir[i].file)
	{
		xdup2(process.redir[i].io, process.redir[i].fd);
		i++;
	}
}

