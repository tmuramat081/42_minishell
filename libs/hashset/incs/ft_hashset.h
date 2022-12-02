/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <mt15hydrangea@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:28:43 by tmuramat          #+#    #+#             */
/*   Updated: 2022/06/23 16:28:43 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASHSET_H
# define FT_HASHSET_H

# define HASHSET_SUCCESS 1
# define HASHSET_FAILURE 0

# define PRIME_1 73
# define PRIME_2 5009

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_hashset {
	size_t	nbits;
	size_t	mask;
	size_t	*data;
	size_t	len;
	size_t	cap;
	size_t (*hash)(const void *);
}	t_hashset;

t_hashset	*ft_hashset_init(size_t(*hash)(const void *data));
void		ft_hashset_clear(t_hashset *set);
void		ft_hashset_delete(t_hashset **set);
int			ft_hashset_insert(t_hashset *set, void *data);
int			ft_hashset_resize(t_hashset *set);

#endif