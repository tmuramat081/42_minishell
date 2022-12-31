#include "minishell.h"

t_env *split_envp(char **envp)
{
	t_env *kv;
	int i = 0;
	int j;
	int k;

	kv = malloc(sizeof(t_env) * 100);
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

t_hashmap	*init_environs(char **envp)
{
	t_hashmap *map;
	t_env *kv;
	size_t i;

	kv = split_envp(envp);
	map = ft_hashmap_init(NULL);
	i = 0;
	while (kv[i].key)
	{
		ft_hashmap_insert(map, kv[i].key, (void *)kv[i].value);
		i++;
	}
	return (map);
}