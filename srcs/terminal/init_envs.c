/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:18:28 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/25 09:18:57 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env	split_str_to_env(char *str)
{
	t_env	env;
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	str = '\0';
	env.key = &str;
	env.value = &str[i + 1];
	return (env);
}

t_hashmap	*init_envs(char **envp)
{
	t_hashmap	*map;
	t_env		env;
	size_t		i;
	size_t		j;

	map = ft_hashmap_init(NULL);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				envp[i][j] = '\0';
				env.key = &envp[i][0];
				env.value = &envp[i][j + 1];
			}
			j++;
		}
		ft_hashmap_insert(map, env.key, (void *)env.value);
		i++;
	}
	return (map);
}
