/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:29 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/30 07:30:54 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include "minishell.h"

void	builtin_unset(char **arg, t_shell *msh)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		ft_hashmap_remove(msh->envs, arg[i]);
		i++;
	}
}
