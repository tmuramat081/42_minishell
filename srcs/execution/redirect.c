/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:17:55 by event             #+#    #+#             */
/*   Updated: 2023/01/29 17:05:27 by tmuramat         ###   ########.fr       */
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

void	close_file(int fd)
{
	if (close(fd) < 0)
		exit(EXIT_FAILURE);
}

/**
 * @brief ファイルをオープンし、オープンしたfdの値を取得する。
 * @detail heredocの場合は入力処理を呼び出し、入力したfdを取得する。
 * @param redirect_type
 * @return int
 */
static int	open_file(t_redirect redirect)
{
	const int	file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int			fd;

	fd = -1;
	if (redirect.type & NODE_RDIR_OUTPUT)
		fd = open(redirect.file, O_WRONLY | O_CREAT | O_TRUNC, file_mode);
	else if (redirect.type & NODE_RDIR_APPEND)
		fd = open(redirect.file, O_WRONLY | O_CREAT | O_APPEND, file_mode);
	else if (redirect.type & NODE_RDIR_INPUT)
		fd = open(redirect.file, O_RDONLY);
	else if (redirect.type & NODE_RDIR_HEREDOC)
		fd = heredoc_redirect(redirect.file);
	if (fd < 0)
	{
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/**
 * @brief リダイレクト先の設定を行う。
 * @details 新規にファイルを開き（open）、入力／出力先に指定（dup2）する。
 * @param process
 */
void	set_redirection(t_process process)
{
	int			old_fd;
	int			new_fd;
	t_redirect	*redirects;

	redirects = process.redirects;
	while (redirects)
	{
		old_fd = open_file(*redirects);
		new_fd = redirects->fd;
		if (dup2(old_fd, new_fd) < 0)
		{
			close(old_fd);
			exit(EXIT_FAILURE);
		}
		close_file(old_fd);
		redirects = redirects->next;
	}
}
