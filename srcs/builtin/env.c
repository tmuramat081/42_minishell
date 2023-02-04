/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:18 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/05 00:08:09 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief ビルトイン - envコマンド
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ft_printf.h"
#include "terminal.h"

static int	print_env(t_hashmap_data *map_data, void *data)
{
	(void)data;
	ft_printf("%s=%s\n", map_data->key, map_data->value);
	return (1);
}

int	builtin_env(char **args, t_shell *msh)
{
	if (!args[1] || !*args[1])
	{
		ft_hashmap_iterate(msh->envs, print_env, NULL);
	}
	return (0);
}
