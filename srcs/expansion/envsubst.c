#include "expansion.h"

/**
 * @brief 環境変数を検索し、見つかればその文字列を返す。見つからなければ空文字列を返す。
 *
 * @param key
 * @param environ
 * @return char*
 */
char    *search_environment(char *key, t_hashmap *environ)
{
    char    *value;

    if (!ft_hashmap_find(environ, key, (void **)&value))
        return (ft_calloc(1, sizeof(char)));
    return (value);
}


bool	is_valid_syntax(char *str, size_t var_start, size_t *i)
{
	if (str[var_start] == '{')
	{
		if (str[*i] == '}')
		{
			(*i)++;
			return (true);
		}
		return (false);
	}
	return(true);
}

size_t	get_var_end(char *str, size_t *i)
{
	while (true)
	{
		(*i)++;
		if (!ft_isalnum(str[*i]) && str[*i] != '_')
			break ;
	}
	return (*i);
}

/**
 * @brief 文字列に含まれる環境変数を展開する。
 *
 * @param word
 * @param environ
 */
void	ft_envsubst(char *str, t_hashmap *environ)
{
	size_t	var_start;
	size_t	var_end;
	size_t	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '{')
				i++;
			var_start = i;
			if (ft_isalpha(str[i]) || str[i] == '_')
			{
				var_end = get_var_end(str, &i);
				if (is_valid_syntax(str, var_start - 1, &i))
				{
					char *var = ft_substr(str, var_start, var_end - var_start);
					char *ret = search_environment(var, environ);
					printf("%s\n", ret);
				}
			}
		}
		i++;
	}
}
