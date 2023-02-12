/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:22:46 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/11 22:22:58 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_hashmap.h"
#include "terminal.h"

/**
 * @file cd.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief ビルトイン - cdコマンド
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "execution.h"

static void	cd_put_error(char *path, char *cmd, t_shell *msh)
{
	errno = ENOENT;
	(void)msh;
	ft_putstr_fd("m-shell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(MSG_NO_FILE_DIR, STDERR_FILENO);
}

int	builtin_cd(char **args, t_shell *msh)
{
	char	*path;

	if (!args || !*args)
		return (1);
	if (!args[1])
		path = ft_getenv("HOME", msh->envs);
	else
		path = args[1];
	if (chdir(path))
	{
		cd_put_error(path, args[0], msh);
		return (1);
	}
	return (0);
}
