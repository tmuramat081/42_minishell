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

#include "minishell.h"
#include <libc.h>
#include <libc.h>
#include "minishell.h"

//envpで取得した環境変数の一覧を分割する。
t_key_value *split_envp(char **envp)
{
	t_key_value *kv;
	//ここに処理を書く
	//文字列を'='で前後に分割し、構造体keyvalueに格納する
	int i = 0;
	int j;
	int k;

	kv = malloc(sizeof(t_key_value) * 100);
	k = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				envp[i][j] = '\0';
				kv[k].key = &envp[i][0];
				kv[k].value = &envp[i][j + 1];
				k++;
			}
			j++;
		}
		i++;
	}
	return (kv);
}

int	compare_key(const void *p_data1, const void *p_data2)
{
	const t_env	*p_str1 = p_data1;
	const t_env	*p_str2 = p_data2;

	return (strcmp(p_str1->key, p_str2->key));
}


t_env	split_envp(char *envp)
{
	t_env env;
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
		{
			envp[i] = '\0';
			env.key = &envp;
			env.value = &envp[i + 1];
		}
		i++;
	}
	return (env);
}


void sort_environs(t_key_value *env)
{
	ft_qsort(env, 5, sizeof(env[0]), compare_key);

}


//ビルトインコマンドとして「export」を実装する。

//オプション指定：なし

//exportの2つの使い方は、
//1. 環境変数を定義すること。
//2. シェル変数を環境変数に、あるいは環境変数をシェル変数に変更すること。

void insert_env(char **args, t_hashmap *map)
{
	size_t i;
	
	i = 0;
	while (args[i])
	{
		// args[i]をkeyとvalueに分割
		split_envp(args[i]);
		t_env env = split_env(args[i])
		ft_hashmap_insert(map, env.key, env.value)
	}
	i++;
}

void export(char **args, t_hashmap *map)
{
	if (args[1])
	{
		insert_env(args, map);
	}
	else 
	{
		;
//	 	print_env()
	}
}
