/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:18 by tmuramat          #+#    #+#             */
/*   Updated: 2023/01/28 04:48:38 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file export.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief ビルトイン - exportコマンド
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "terminal.h"
#include "ft_printf.h"
#include "libft.h"
#include "ft_pqueue.h"
#include "ft_hashmap.h"

int	compare_key(const void *p_data1, const void *p_data2)
{
	const t_env	*env1 = p_data1;
	const t_env	*env2 = p_data2;
	int			res;

	res = ft_strcmp(env1->key, env2->key);
	if (res > 0)
		return (1);
	else if (res < 0)
		return (-1);
	return (0);
}

/**
 * @brief ハッシュテーブルの値を優先度付きキューに格納する
 *
 *
*/
int	set_priority_queue(t_hashmap_data *hash_data, void *p_pqueue)
{
	t_env		*env;
	t_pqueue	*pqueue;

	pqueue = (t_pqueue *)p_pqueue;
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (HASHMAP_FAILURE);
	env->key = hash_data->key;
	env->value = hash_data->value;
	ft_priority_queue_push(pqueue, env);
	return (HASHMAP_SUCCESS);
}

void	sort_envs(t_hashmap *envs)
{
	t_env		*env;
	t_pqueue	*pqueue;

	pqueue = ft_priority_queue_init(32, compare_key);
	ft_hashmap_iterate(envs, set_priority_queue, pqueue);
	while (!ft_priority_queue_is_empty(pqueue))
	{
		ft_priority_queue_pop(pqueue, (void **)&env);
		ft_printf("dexlare -x %s=\"%s\"\n", env->key, env->value);
		free(env);
	}
}

void	print_envs(t_hashmap *envs)
{
	sort_envs(envs);
}

/**
 * @brief 文字列をkeyとvalueに分解し、env構造体に格納する。
 *
 * @param str 分割する文字列
 * @return t_env
 */
t_env	parse_environ(char *str)
{
	t_env	environ;
	char	*p_sep;

	environ = (t_env){};
	p_sep = strchr(str, '=');
	if (p_sep)
	{
		*p_sep = '\0';
		environ.key = str;
		environ.value = (char *)(p_sep+1);
		puts(environ.key);
		puts(environ.value);
	}
	return (environ);
}

/**
 * @brief 文字列の配列を環境変数に追加する。
 *
 * @param args
 * @param map
 */
void insert_env(char **args, t_hashmap *environs)
{
	size_t i;
	t_env new_env;

	i = 0;
	while (args[i] != NULL)
	{
		new_env = parse_environ(args[i]);
		if (new_env.key && new_env.value)
			ft_hashmap_insert(environs, new_env.key, new_env.value);
		i++;
	}
}

/**
 * @brief ビルトイン関数：export
 *
 * @param args
 * @param msh
 * @return int
 */
int	builtin_export(char **args, t_shell *msh)
{
	int	argc;

	argc = ft_matrixlen((const char **)args);
	if (argc == 1)
		print_envs(msh->envs);
	else
		insert_env(&args[1], msh->envs);
	return (0);
}
