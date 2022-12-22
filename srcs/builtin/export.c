/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:58:18 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/22 08:58:20 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_key(const void *p_data1, const void *p_data2)
{
	const t_env	*p_str1 = p_data1;
	const t_env	*p_str2 = p_data2;

	return (strcmp(p_str1->key, p_str2->key));
}

void	sort_environs(t_env *env)
{
	ft_qsort(env, 5, sizeof(env[0]), compare_key);

}
