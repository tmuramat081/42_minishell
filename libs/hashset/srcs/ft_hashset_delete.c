/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <mt15hydrangea@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:19:46 by tmuramat          #+#    #+#             */
/*   Updated: 2022/06/23 22:19:46 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashset.h"

static void	*ft_memset(void *p, int c, size_t len)
{
	void	*ret;

	ret = p;
	while (len--)
	{
		*(unsigned char *)p = (unsigned char)c;
		p++;
	}
	return (ret);
}

void	ft_hashset_clear(t_hashset *set)
{
	ft_memset(set->data, 0, sizeof(size_t) * set->cap);
	set->len = 0;
}

void	ft_hashset_delete(t_hashset **set)
{
	if (!*set)
		return ;
	free((*set)->data);
	(*set)->data = NULL;
	free(*set);
	(*set) = NULL;
}
