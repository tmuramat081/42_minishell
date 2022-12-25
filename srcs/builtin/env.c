/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:18 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/22 08:58:20 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
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

static t_env	split_envptr(char *envp)
{
	t_env env;
	size_t	i;

	i = 0;
	while (envp[i] != '\0' && envp[i] != '=')
	{
		i++;
	}
	envp[i] = '\0';
	env.key = envp;
	env.value = &envp[i + 1];
	return (env);
}

static void insert_env(char **args, t_hashmap *map)
{
	size_t i;
	t_env env;
	
	i = 0;
	while (args[i] != NULL)
	{
		env = split_envptr(args[i]);
		ft_hashmap_insert(map, env.key, env.value);
		i++;
	}
}

void env(char **args, t_hashmap *map)
{
	if (!args || !*args)
	{
		print_envs(map);
	}
}
