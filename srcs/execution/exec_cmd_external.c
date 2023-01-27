/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:18:48 by event             #+#    #+#             */
/*   Updated: 2023/01/27 01:18:49 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"
#include "ft_printf.h"
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
	ft_execvpe(process.argv[0], process.argv, construct_environ(msh->envs));
	exit(EXIT_FAILURE);
}
