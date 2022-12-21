#include "minishell.h"

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

