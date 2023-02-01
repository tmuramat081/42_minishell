#include "ft_hashmap.h"
#include "terminal.h"

char	*ft_getenv(char *key, t_hashmap *envs)
{
	char *p_value;

	if (!ft_hashmap_find(envs, key, (void **)&p_value))
		return (NULL);
	return (p_value);
}

int	ft_setenv(t_env *env, t_hashmap *envs, int overwrite)
{
	if (overwrite == 0 && !ft_hashmap_find(envs, env->key, NULL))
		return (0);
	ft_hashmap_insert(envs, env->key, env->value);
	return (0);
}

/**
 * @file cd.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief ビルトイン - cdコマンド
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "execution.h"

int	builtin_cd(char **args, t_shell *msh)
{
	char *path;

	if (!args || !*args)
		return (1);
	if (!args[1])
		path = ft_getenv("HOME", msh->envs);
	else
		path = args[1];
	if (chdir(path))
	{
		ft_putendl_fd("error", 2);
		return (+1);
	}
	return (0);
}
