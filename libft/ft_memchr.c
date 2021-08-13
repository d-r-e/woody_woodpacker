/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:22:13 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/14 12:21:39 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	char	charac;

	str = (char *)s;
	charac = (char)c;
	while (n--)
	{
		if (*str == charac)
			return (str);
		str++;
	}
	return (0);
}
