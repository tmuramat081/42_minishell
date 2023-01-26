#include "expansion.h"
#include <assert.h>

typedef struct s_wordwxp
{
	size_t	we_wordc;		/* Count of words matched.  */
	char	**we_wordv;		/* List of expanded words.  */
	size_t	we_offs;		/* Slots to reserve in `we_wordv'.  */
}	t_wordexp;

static char *_w_addchar(char *buff, size_t *act_len, size_t *max_len, char ch)
{
	char *old_buff;

	if (*act_len == *max_len)
	{
		old_buff = buff;
		assert (!buff || *max_len != 0);
		*max_len += 100;
		buff = (char *)ft_realloc(buff, 1 + *max_len);
		if (!buff)
			free(old_buff);
	}
	if (buff != NULL)
	{
		buff[*act_len] = ch;
		buff[++(*act_len)] = '\0';
	}
	return (buff);
}

static char	*_w_addmem(char *buff, size_t *act_len, size_t *max_len, const char *str, size_t len)
{
	char *old_buff;

	if (*act_len + len > *max_len)
	{
		old_buff = buff;
		assert (buff == NULL || *max_len != 0);
		*max_len += ft_max(2 * len, 100);
		buff = ft_realloc(old_buff, 1 + *max_len);
		if (!buff)
			free(old_buff);
	}
	if (buff)
	{
		*((char *) ft_mempcpy(&buff[*act_len], str, len)) = '\0';
		*act_len += len;
	}
	return (buff);
}

static char *_w_addstr(char *buff, size_t *act_len, size_t *max_len, const char *str)
{
	size_t len;

	assert(str != NULL);
	len = strlen(str);
	return (add_mem(buff, act_len, max_len, str, len));
}

static char *_w_newword (size_t *act_len, size_t *max_len)
{
	*act_len = *max_len = 0;
	return NULL;
}

static int parse_dollars(char **word, size_t *word_len, size_t *max_len, const char *words, size_t *offset, int flags)
{

}

int ft_wordexp_env(const char *words, t_wordexp *wordexp, int flag)
{
	size_t words_offset;
	size_t word_length;
	size_t max_length;
	char *word;

	word = ft_newword(word_length, max_length);
	while(words[words_offset])
	{
		if (words[words_offset])
		{
			parse_dollar(&word,
		}
		words_offset++;
	}
}
