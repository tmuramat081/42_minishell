#include "expansion.h"
#include "libft.h"

/**
 * @brief シェルの文法に従って文字列を展開する。
 *
 * @param word　展開元となる文字列
 * @param buff 展開された文字列が格納されるアドレス
 * @param environ　展開に使用する環境変数
 * @return int 成功した場合は0を返す。構文エラーの場合は対応する値を返す。
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
		else if (words[offset] == '\'' || words[offset] == '"')
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
	return (FTWRDE_SUCCESS);
}
