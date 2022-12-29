/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:18 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/29 23:24:04 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"


static int print_env(t_hashmap_data *map_data, void *data)
{
	(void)data;
	ft_printf("%s=\"%s\"\n", map_data->key, map_data->value);
	return (1);
}

static void	print_envs(t_hashmap *map)
{
	ft_hashmap_iterate(map, print_env, NULL);
}

void env(char **args, t_hashmap *map)
{
	if (!args || !*args)
	{
		print_envs(map);
	}
}
