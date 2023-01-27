#include "execution.h"
#include "libft.h"

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

char *w_addstr(char *buff, size_t *act_len, size_t *max_len, const char *str)
{
	size_t len;

	assert(str != NULL);
	len = ft_strlen(str);
	return (_w_addmem(buff, act_len, max_len, str, len));
}

char *w_addchar(char *buff, size_t *act_len, size_t *max_len, char ch)
{
	char *old_buff;

	if (*act_len == *max_len)
	{
		old_buff = buff;
		assert (!buff || *max_len != 0);
		*max_len += 10;
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

char *w_newword (size_t *act_len, size_t *max_len)
{
	*act_len = *max_len = 0;
	return (NULL);
}

