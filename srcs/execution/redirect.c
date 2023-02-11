/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:17:55 by event             #+#    #+#             */
/*   Updated: 2023/02/11 17:09:18 by tmuramat         ###   ########.fr       */
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
void	set_redirection(t_process process, t_shell *msh)
{
	int			old_fd;
	int			new_fd;
	t_redirect	*redirects;

	if (ast_count_redirects(process.redirects) == 0)
		return ;
	redirects = process.redirects;
	while (redirects)
	{
		old_fd = open_file(redirects->file, redirects->type);
		if (old_fd < 0)
		{
			shell_perror(redirects->file, msh, 1);
			return ;
		}
		new_fd = redirects->fd;
		xdup2(old_fd, new_fd);
		xclose(old_fd);
		redirects = redirects->next;
	}
}
