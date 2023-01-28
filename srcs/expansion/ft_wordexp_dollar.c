#include "expansion.h"
#include "libft.h"

/**
 * @brief 環境変数を検索し、見つかればその文字列を返す。見つからなければ空文字列を返す。
 *
 * @param key
 * @param environ
 * @return char*
 */
char	*search_environment(char *key, t_hashmap *environ)
{
	char	*value;

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
	return (true);
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
 * @brief '$'以降の文字列を走査する。
 *
 * @param str
 * @param offset
 * @param environ
 */
int	we_parse_dollar(char *words, char **buff, t_wordexp *wp, size_t *offset)
{
	size_t	var_start;
	size_t	var_end;
	char	*var;

	if (words[*offset] == '{')
		++*offset;
	var_start = *offset;
	if (ft_isalpha(words[*offset]) || words[*offset] == '_')
	{
		forward_to_var_end(words, offset);
		var_end = *offset;
		if (is_valid_syntax(words, var_start - 1, offset))
		{
			var = ft_substr(words, var_start, var_end - var_start);
			*buff = w_addstr(*buff, wp, search_environment(var, wp->envs));
		}
		else
			abort();
	}
	return (FTWRDE_SUCCESS);
}
