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

/*

int	compare_key(const void *p_data1, const void *p_data2)
{
	const t_env	*p_str1 = p_data1;
	const t_env	*p_str2 = p_data2;

	return (strcmp(p_str1->key, p_str2->key));
}

void sort_environs(t_env *env)
{
	ft_qsort(env, 5, sizeof(env[0]), compare_key);

}
*/

int print_env(t_hashmap_data *map_data, void *data)
{
	(void)data;
	ft_printf("declare -x %s=\"%s\"\n", map_data->key, map_data->value);
	return (1);
}

void	print_envs(t_hashmap *map)
{
	ft_hashmap_iterate(map, print_env, NULL);
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
