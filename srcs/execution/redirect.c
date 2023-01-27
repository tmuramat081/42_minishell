/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:17:55 by event             #+#    #+#             */
/*   Updated: 2023/01/27 01:17:56 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "execution.h"
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
 * @brief ファイルをオープンする。
 *
 * @param redirect_type
 * @return int
 */
static int	open_file(t_redirect redirect)
{
	const int	file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	if (redirect.dir & NODE_RDIR_OUTPUT)
		return (open(redirect.file, O_WRONLY | O_CREAT | O_TRUNC, file_mode));
	else if (redirect.dir & NODE_RDIR_APPEND)
		return (open(redirect.file, O_WRONLY | O_CREAT | O_APPEND, file_mode));
	return (open(redirect.file, O_RDONLY));
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
		if (old_fd == -1)
		{
			exit(EXIT_FAILURE);
		}
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
