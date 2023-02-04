/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:18:28 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/04 23:41:14 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
/*
 * @file environs.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 環境変数の初期化
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */

char	*ft_getenv(const char *key, t_hashmap *envs)
{
	char	*p_value;

	if (!ft_hashmap_find(envs, key, (void **)&p_value))
		return (NULL);
	return (p_value);
}

int	ft_putenv(t_env *env, t_hashmap *envs)
{
	int	ok;

	ok = ft_hashmap_insert(envs, env->key, env->value);
	if (!ok)
		return (-1);
	return (0);
}

int	ft_setenv(t_env *env, t_hashmap *envs, int overwrite)
{
	int	ok;

	if (overwrite == 0)
	{
		ok = ft_hashmap_find(envs, env->key, NULL);
		if (!ok)
			return (0);
	}
	return (ft_putenv(env, envs));
}

int	ft_unsetenv(const char *key, t_hashmap *envs)
{
	int	ok;

	ok = ft_hashmap_remove(envs, key);
	if (!ok)
		return (-1);
	return (0);
}

/**
 * @brief 文字列をkeyとvalueに分解し、env構造体に格納する。
 *
 * @param str 分割する文字列
 * @return t_env
 */
t_env	parse_environ(const char *str)
{
	t_env	environ;
	char	*p_sep;

	if (!str)
		exit(EXIT_FAILURE);
	environ = (t_env){};
	p_sep = ft_strchr(str, '=');
	if (p_sep)
	{
		environ.key = ft_strndup(str, p_sep - str);
		environ.value = ft_strdup(p_sep + 1);
	}
	return (environ);
}

/**
 * @brief グローバル変数'environ'から環境変数を取得する
 *
 * @return t_hashmap*
 */
t_hashmap	*init_environ(void)
{
	extern char	**environ;
	t_hashmap	*env_table;
	t_env		env;
	size_t		i;

	env_table = ft_hashmap_init(NULL, NULL);
	i = 0;
	while (environ[i])
	{
		env = parse_environ(environ[i]);
		ft_setenv(&env, env_table, 1);
		i++;
	}
	return (env_table);
}
