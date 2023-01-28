#include "expansion.h"
#include "libft.h"

static char	*_w_addmem(char *buff, t_wordexp *we, const char *str, size_t len)
{
	char	*old_buff;

	if (we->act_len + len > we->max_len)
	{
		old_buff = buff;
		if (buff || we->max_len)
			exit(0);
		we->max_len += ft_max(2 * len, 100);
		buff = ft_realloc(old_buff, 1 + we->max_len);
		if (!buff)
			free(old_buff);
	}
	if (buff)
	{
		*((char *) ft_mempcpy(&buff[we->act_len], str, len)) = '\0';
		we->act_len += len;
	}
	return (buff);
}

char	*w_addstr(char *buff, t_wordexp *wp, const char *str)
{
	size_t	len;

	if (!str)
		exit (1);
	len = ft_strlen(str);
	return (_w_addmem(buff, wp, str, len));
}

char	*w_addchar(char *buff, t_wordexp *wp, char ch)
{
	char	*old_buff;

	if (wp->act_len == wp->max_len)
	{
		old_buff = buff;
		if (buff || wp->max_len)
			exit(0);
		wp->max_len += 10;
		buff = (char *)ft_realloc(buff, 1 + wp->max_len);
		if (!buff)
			free(old_buff);
	}
	if (buff != NULL)
	{
		buff[wp->act_len] = ch;
		buff[++wp->act_len] = '\0';
	}
	return (buff);
}

t_wordexp	w_newword(t_hashmap *environs)
{
	t_wordexp	wordexp;

	wordexp.act_len = 0;
	wordexp.max_len = 0;
	wordexp.envs = environs;
	return (wordexp);
}
