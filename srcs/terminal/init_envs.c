/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:18:28 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/29 23:22:08 by tmuramat         ###   ########.fr       */
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
	str[i] = '\0';
	env.key = &str[0];
	env.value = &str[i + 1];
	return (env);
}

t_hashmap	*init_envs(char **envp)
{
	t_hashmap	*envs;
	t_env		env;
	size_t		i;

	envs = ft_hashmap_init(NULL);
	i = 0;
	while (envp[i])
	{
		env = split_str_to_env(envp[i]);
		ft_hashmap_insert(envs, env.key, (void *)env.value);
		i++;
	}
	return (envs);
}
