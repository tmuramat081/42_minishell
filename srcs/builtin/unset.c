/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:29 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/05 00:38:42 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file unset.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief ビルトイン - unsetコマンド
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "ft_hashmap.h"
#include "terminal.h"

int	builtin_unset(char **args, t_shell *msh)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (!ft_unsetenv(args[i], msh->envs))
			return (-1);
		i++;
	}
	return (0);
}
