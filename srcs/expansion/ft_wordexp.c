#include "expansion.h"
#include "libft.h"

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

/**
 * @brief 環境変数が波括弧{}で閉じられているか判定する 
 * 
 * @param str 
 * @param var_start 
 * @param offset 
 * @return true 
 * @return false 
 */
bool	is_valid_syntax(char *str, size_t var_start, size_t *offset)
{
	if (str[var_start] == '{')
	{
		if (str[*offset] == '}')
		{
			++*offset;
			return (true);
		}
		return (false);
	}
	return(true);
}

/**
 * @brief 環境変数の終端までインデックスを進める。
 * 
 * @param str 
 * @param offset 
 */
void	forward_to_var_end(char *str, size_t *offset)
{
	while (true)
	{
		++*offset;
		if (!ft_isalnum(str[*offset]) && str[*offset] != '_')
			break ;
	}
}

/**
 * @brief $以降の文字列を走査する。 
 * 
 * @param str 
 * @param offset 
 * @param environ 
 */
char *parse_dollar(char *str, size_t *offset, t_hashmap *environ)
{
	size_t	var_start;
	size_t	var_end;
	char	*var;

	if (str[*offset] == '{')
		++*offset;
	var_start = *offset;
	if (ft_isalpha(str[*offset]) || str[*offset] == '_')
	{
		forward_to_var_end(str, offset);
		var_end = *offset;
		if (is_valid_syntax(str, var_start - 1, offset))
		{
			var = ft_substr(str, var_start, var_end - var_start);
			return(search_environment(var, environ));
		}
		else
			abort();
	}
	return (NULL);
}

/**
 * @brief 文字列に含まれる環境変数を展開する。
 *
 * @param word
 * @param environ
 * @return int 成功した場合は0を返す。構文エラーの場合は1を返す。 
 */
int	ft_wordexp_env(char *words, char **buff, t_hashmap *environ)
{
	size_t		offset;
	size_t		act_len;
	size_t		max_len;
	char 		*env;

	*buff = w_newword(&act_len, &max_len);
	offset = 0;
	while(words[offset])
	{
		if (words[offset] == '$')
		{
			++offset;
			env = parse_dollar(words, &offset, environ);
			*buff = w_addstr(*buff, &act_len, &max_len, env);

		}
		else
		{
			*buff = w_addchar(*buff, &act_len, &max_len, words[offset]);
			++offset;
		}
	}
	return (0);
}
