/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:18 by tmuramat          #+#    #+#             */
/*   Updated: 2023/01/01 13:29:11 by tmuramat         ###   ########.fr       */
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
#include "minishell.h"
#include "ft_printf.h"
#include "libft.h"
#include "ft_pqueue.h"
#include "ft_hashmap.h"

int	compare_key(const void *p_data1, const void *p_data2)
{
	const t_env	*env1 = p_data1;
	const t_env	*env2 = p_data2;

	return (ft_strcmp(env1->key, env2->key));
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
		env = ft_priority_queue_pop(pqueue);
		ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
	}
}


void	print_envs(t_hashmap *envs)
{
	sort_envs(envs);
}

t_env	split_envptr(char *envp)
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

void insert_env(char **args, t_hashmap *map)
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
