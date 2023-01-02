/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mempcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:27:58 by tmuramat          #+#    #+#             */
/*   Updated: 2023/01/02 20:01:40 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mempcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cast_d;
	unsigned char	*cast_s;

	if (!dst && !src)
		return (NULL);
	cast_d = (unsigned char *)dst;
	cast_s = (unsigned char *)src;
	while (n--)
		*(cast_d++) = *(cast_s++);
	return (cast_d);
}