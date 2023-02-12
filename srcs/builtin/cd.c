/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:22:46 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/12 15:20:13 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "ft_hashmap.h"
#include "terminal.h"

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
		errno = ENOENT;
		builtin_perror(MSG_NO_FILE_DIR, path, args[0], msh);
		return (1);
	}
	return (0);
}
