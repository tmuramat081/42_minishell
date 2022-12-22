/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:29 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/22 08:58:35 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include "minishell.h"

void	unset(char **arg, t_hashmap *map)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		ft_hashmap_remove(map, arg[i]);
		i++;
	}
}
