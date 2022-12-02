/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset_modifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <mt15hydrangea@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:04:58 by tmuramat          #+#    #+#             */
/*   Updated: 2022/06/23 23:04:58 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashset.h"

#define REHASH_THRESHOLD 0.8

static bool	is_over_load_factor(t_hashset *set)
{
	if ((double)set->cap * REHASH_THRESHOLD < set->len)
		return (true);
	return (false);
}

static int	hash_insert(t_hashset *set, void *data)
{
	size_t	value;
	size_t	i;

	value = set->hash(data);
	i = set->mask & (value * PRIME_1);
	while (set->data[i] != 0)
	{
		if (set->data[i] == value)
			return (HASHSET_FAILURE);
		else
			i = set->mask & (i + PRIME_2);
	}
	set->len += 1;
	set->data[i] = value;
	return (HASHSET_SUCCESS);
}

int	ft_hashset_insert(t_hashset *set, void *data)
{
	bool	ret;

	ret = hash_insert(set, data);
	if (is_over_load_factor(set) == true)
	{
		if (ft_hashset_resize(set) == HASHSET_FAILURE)
			return (HASHSET_FAILURE);
	}
	return (ret);
}
