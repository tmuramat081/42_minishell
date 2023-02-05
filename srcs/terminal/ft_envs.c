
#include "terminal.h"
/*
 * @file environs.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 環境変数の登録・更新・削除・取得
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
