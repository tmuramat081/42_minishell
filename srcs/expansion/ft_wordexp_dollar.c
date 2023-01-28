#include "expansion.h"
#include "libft.h"

/**
 * @brief '$'以降の文字列を走査する。
 * @detail '{}'以外の括弧は未実装
 * @param str
 * @param offset
 * @param environ
 */
int	we_parse_dollar(char *words, char **buff, t_wordexp *wp, size_t *offset)
{
	if (words[*offset] == '"' || words[*offset] == '\0')
	{
		*buff = w_addchar(*buff, wp, '$');
		return (FTWRDE_SUCCESS);
	}
	else
	{
		return (we_parse_params(words, buff, wp, offset));
	}
	return (FTWRDE_SUCCESS);
}
