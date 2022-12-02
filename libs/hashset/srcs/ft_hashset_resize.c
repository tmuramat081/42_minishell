/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset_resize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <mt15hydrangea@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:47:55 by tmuramat          #+#    #+#             */
/*   Updated: 2022/06/25 00:47:55 by tmuramat         ###   ########.fr       */
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

static void	hash_reinsert(t_hashset *set, size_t *new_data, size_t value)
{
	size_t	i;

	if (value == 0)
		return ;
	i = set->mask & (value * PRIME_1);
	while (new_data[i] != 0)
	{
		if (new_data[i] == value)
			return ;
		i = set->mask & (i + PRIME_2);
	}
	set->len += 1;
	new_data[i] = value;
}

int	ft_hashset_resize(t_hashset *set)
{
	size_t	*new_data;
	size_t	prev_cap;
	size_t	i;

	prev_cap = set->cap;
	set->nbits += 1;
	set->cap = (size_t)(1 << set->nbits);
	set->mask = set->cap - 1;
	new_data = malloc(sizeof(size_t) * set->cap);
	if (!new_data)
		return (HASHSET_FAILURE);
	ft_memset(new_data, 0, sizeof(size_t) * set->cap);
	set->len = 0;
	i = 0;
	while (i < prev_cap)
	{
		hash_reinsert(set, new_data, set->data[i]);
		i++;
	}
	free(set->data);
	set->data = new_data;
	return (HASHSET_SUCCESS);
}
