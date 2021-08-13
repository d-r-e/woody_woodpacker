/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:59:41 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/14 12:27:48 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *s;
	char *d;

	s = (char*)src;
	d = (char*)dst;
	if (d > s)
	{
		while (len--)
			d[len] = s[len];
	}
	else
		return (ft_memcpy(dst, src, len));
	return ((void*)dst);
}
