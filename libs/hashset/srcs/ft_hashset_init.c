/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <mt15hydrangea@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:04:35 by tmuramat          #+#    #+#             */
/*   Updated: 2022/06/23 23:04:35 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashset.h"

#define INIT_NBITS 16

size_t	default_hash(const void	*data)
{
	return ((size_t)data);
}

t_hashset	*ft_hashset_init(size_t(*hash)(const void *data))
{
	t_hashset	*new_set;

	new_set = malloc(sizeof(t_hashset));
	if (!new_set)
		return (NULL);
	new_set->nbits = INIT_NBITS;
	new_set->cap = (size_t)(1 << new_set->nbits);
	new_set->mask = new_set->cap - 1;
	if (!hash)
		new_set->hash = default_hash;
	else
		new_set->hash = hash;
	new_set->data = malloc(sizeof(size_t) * new_set->cap);
	if (!new_set->data)
	{
		free(new_set);
		return (NULL);
	}
	ft_hashset_clear(new_set);
	return (new_set);
}
