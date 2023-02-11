/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:34:35 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/11 22:34:36 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "expansion.h"
#include "libft.h"
#include <assert.h>

static char	*_we_addmem(char *buff, t_wordexp *we, const char *str, size_t len)
{
	char	*old_buff;
	char	*p_end;

	if (we->act_len + len > we->max_len)
	{
		old_buff = buff;
		we->max_len += (len * 2);
		buff = ft_realloc(old_buff, 1 + we->max_len);
		if (!buff)
			free(old_buff);
	}
	if (buff)
	{
		p_end = ft_mempcpy(&buff[we->act_len], str, len);
		*p_end = '\0';
		we->act_len += len;
	}
	return (buff);
}

char	*we_addstr(char *buff, t_wordexp *wp, const char *str)
{
	size_t	len;

	if (!str)
		exit (EXIT_FAILURE);
	len = ft_max(1, ft_strlen(str));
	return (_we_addmem(buff, wp, str, len));
}

char	*we_addchar(char *buff, t_wordexp *wp, char ch)
{
	char	*old_buff;

	if (wp->act_len == wp->max_len)
	{
		old_buff = buff;
		wp->max_len += 16;
		buff = (char *)ft_realloc(old_buff, 1 + wp->max_len);
		if (!buff)
			free(old_buff);
	}
	if (buff)
	{
		buff[wp->act_len] = ch;
		buff[++wp->act_len] = '\0';
	}
	return (buff);
}

t_wordexp	we_newword(t_hashmap *environs)
{
	t_wordexp	wordexp;

	wordexp.act_len = 0;
	wordexp.max_len = 0;
	wordexp.envs = environs;
	return (wordexp);
}
