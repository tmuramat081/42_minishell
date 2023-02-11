/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:28:02 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/11 20:29:54 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file error.c
 * @brief プログラムに共通で使用するエラーハンドラー関数
 * @date 2023-02-11
 */

#include "terminal.h"

/**
 * @brief プロセスを正しい方法で終了する。
 *
 * @detail 子プロセスの場合はexit、親プロセスの場合はreturnを呼び出す。
 * @param status
 * @param msh
 */
void	maybe_exit(int status, t_shell *msh)
{
	extern int	g_status;

	if (msh && msh->is_child_process == false)
	{
		g_status = status;
		return ;
	}
	exit(status);
}

/*
 * @brief シェルに共通で使用するエラーハンドラー
 *
 * @detail 仕様上、errnoがEISDIRである場合のみ"Is a directory"を"is a dorectory"に置き換える。
 * @param string　エラーの詳細情報（主にコマンド・引数名が入る）
 * @param msh シェルの管理情報
 * @param status　設定するコマンドの終了ステータス
 */
void	shell_perror(const char *string, t_shell *msh, int status)
{
	extern int	g_status;

	ft_putstr_fd("m-shell: ", STDERR_FILENO);
	if (errno == EISDIR)
		ft_putendl_fd("is a directory", STDERR_FILENO);
	else
		perror(string);
	return (maybe_exit(status, msh));
}
