/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:18:48 by event             #+#    #+#             */
/*   Updated: 2023/02/11 04:25:46 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"
#include "ft_printf.h"
#include "constant.h"
#include <unistd.h>
#include <fcntl.h>


/**
 * @brief 外部コマンドを実行する
 *
 * @param process コマンド実行の管理情報
 * @param msh シェルの管理情報
 */
void	exec_external_command(t_process process, t_shell *msh)
{
	extern int	g_status;
	char		*cmd_name;

	if (!process.argv || !process.argv[0])
		return ;
	cmd_name = process.argv[0];
	ft_execvpe(process.argv[0], process.argv, construct_environ(msh->envs));
	if (errno == EISDIR)
	{
		shell_perror(cmd_name, msh);
		exit(126);
	}
	else if (errno == EACCES)
	{
		shell_perror(cmd_name, msh);
		exit(126);
	}
	shell_perror(cmd_name, msh);
	exit(127);
}
