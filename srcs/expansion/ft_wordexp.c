#include "expansion.h"
#include "libft.h"

/**
 * @brief 文字列に含まれる環境変数を展開する。
 *
 * @param word
 * @param environ
 * @return int 成功した場合は0を返す。構文エラーの場合は0以外を返す。
 */
int	ft_wordexp(char *words, char **buff, t_hashmap *environs)
{
	size_t		offset;
	t_wordexp	wp;

	wp = w_newword(environs);
	offset = 0;
	while (words[offset])
	{
		if (words[offset] == '$')
		{
			++offset;
			we_parse_dollar(words, buff, &wp, &offset);
		}
		else if (words[offset] == '\'' || words[offset] == '\"')
		{
			++offset;
			we_parse_quote(words, buff, &wp, &offset);
		}
		else
		{
			*buff = w_addchar(*buff, &wp, words[offset]);
			++offset;
		}
	}
	puts(*buff);
	return (FTWRDE_SUCCESS);
}
