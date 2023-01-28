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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:18 by tmuramat          #+#    #+#             */
/*   Updated: 2023/01/01 13:03:50 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "terminal.h"


static int print_env(t_hashmap_data *map_data, void *data)
{
	(void)data;
	ft_printf("%s=%s\n", map_data->key, map_data->value);
	return (1);
}

static void	print_envs(t_hashmap *map)
{
	ft_hashmap_iterate(map, print_env, NULL);
}

int	builtin_env(char **args, t_shell *msh)
{
	if (!args[1] || !*args[1])
	{
		print_envs(msh->envs);
	}
	return (0);
}
