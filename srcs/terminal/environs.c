/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:18:28 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/30 01:12:34 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 環境変数の文字列を'='で分割する
 *
 * @param str_env
 * @return t_env
 */
t_env	parse_envp(char *str_env)
{
	t_env	env;
	size_t	i;

	i = 0;
	while (str_env[i] != '\0' && str_env[i] != '=')
		i++;
	str_env[i] = '\0';
	env.key = &str_env[0];
	env.value = &str_env[i + 1];
	return (env);
}

/**
 * @brief グローバル変数'environ'から環境変数を取得する
 *
 * @return t_hashmap*
 */
t_hashmap	*init_environ()
{
	extern char	**environ;
	t_hashmap	*env_table;
	t_env		env;
	size_t		i;

	env_table = ft_hashmap_init(NULL);
	i = 0;
	while (environ[i])
	{
		env = parse_envp(environ[i]);
		ft_hashmap_insert(env_table, env.key, (void *)env.value);
		i++;
	}
	return (env_table);
}
