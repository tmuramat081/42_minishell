#include "expansion.h"

/**
 * @brief ダブルクオート’"'以降の文字列を走査する。
 *
 * @param str
 * @param buff
 * @param offset
 */
static int	we_parse_double_quote(char *words, char **buff, t_wordexp *wp, size_t *offset)
{
	while (words[*offset])
	{
		if (words[*offset] == '"')
		{
			++*offset;
			return (FTWRDE_SUCCESS);
		}
		else if (words[*offset] == '$')
		{
			return (we_parse_dollar(words, buff, wp, offset));
		}
		else
		{
			*buff = we_addchar(*buff, wp, words[*offset]);
			if (!*buff)
				return (FTWRDE_NOSPACE);
		}
		++*offset;
	}
	return (FTWRDE_SYNTAX);
}

static int	we_parse_single_quote(char *words, char **buff, t_wordexp *wp, size_t *offset)
{
	while (words[*offset])
	{
		if (words[*offset] == '\'')
		{
			++*offset;
			return (FTWRDE_SUCCESS);
		}
		else
		{
			*buff = we_addchar(*buff, wp, words[*offset]);
			if (!*buff)
				return (FTWRDE_NOSPACE);
		}
		++*offset;
	}
	return (FTWRDE_SYNTAX);
}

int		we_parse_quote(char *words, char **buff, t_wordexp *wp, size_t *offset)
{
	if (words[*offset - 1] == '\'')
	{
		we_parse_single_quote(words, buff, wp, offset);
	}
	else if (words[*offset - 1] == '"')
	{
		we_parse_double_quote(words, buff, wp, offset);
	}
	return (0);
}
