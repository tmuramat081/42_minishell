/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 06:18:28 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/06 01:04:45 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include <ctype.h>

static bool is_valid_key(const char *key)
{
	size_t	i;

	if (!key || !*key)
		return (false);
	if (ft_isdigit(key[0]))
		return (false);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
/**
 * @brief 文字列をkeyとvalueに分解し、env構造体に格納する。
 *
 * @param str 分割する文字列
 * @return t_env
 */
t_env	parse_environ(const char *str)
{
	t_env	env;
	char	*p_sep;

	if (!str)
		exit(EXIT_FAILURE);
	p_sep = ft_strchrnul(str, '=');
	env.key = ft_strndup(str, p_sep - str);
	if (is_valid_key(env.key) == false)
	{
		free(env.key);
		return ((t_env){NULL, NULL});
	}
	if (*p_sep == '\0')
		env.value = ft_strdup("");
	else
		env.value = ft_strdup(p_sep + 1);
	if (!env.value)
	{
		free(env.key);
		return ((t_env){NULL, NULL});
	}
	return (env);
}

/**
 * @brief グローバル変数'environ'から環境変数を取得する。
 * @detail $OLDPWDは空文字列で初期化する。
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
		if (env.key && env.value)
			ft_setenv(&env, env_table, 1);
		i++;
	}
	env = parse_environ("OLDPWD");
	ft_putenv(&env, env_table);
	return (env_table);
}
