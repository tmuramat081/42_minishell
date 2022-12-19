#include <libc.h>
#include "minishell.h"

typedef struct s_key_value
{
	char *key;
	char *value;
} t_key_value;

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

int compare_key(const void *p_data1, const void *p_data2)
{
	const t_key_value *p_str1 = p_data1;
	const t_key_value *p_str2 = p_data2;
	
	return strcmp(p_str1->key, p_str2->key);
}

void sort_environs(t_key_value *env)
{
	ft_qsort(env, 5, sizeof(env[0]), compare_key);
}

int split_envp(char **envp)
{
	t_key_value *kv;

	kv = split_envp(envp);
	sort_environs(kv);
	int i = 0;
	while (kv[i].key)
	{
		i++;
	}
	return (0);
}
