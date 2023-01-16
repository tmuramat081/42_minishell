/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap_iterate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:42:19 by kkohki            #+#    #+#             */
/*   Updated: 2023/01/16 09:20:04 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"

int	ft_hashmap_iterate(t_hashmap *map, int(*f)(t_hashmap_data *, void *),
	void *item)
{
	size_t			i;
	int				status;
	t_hashmap_data	data;

	i = 0;
	while (i < map->cap)
	{
		if (map->data[i].in_use == true)
		{
			data = map->data[i];
			status = f(&data, item);
			if (status != HASHMAP_SUCCESS)
			{
				return (status);
			}
		}
		i++;
	}
	return (HASHMAP_SUCCESS);
}
