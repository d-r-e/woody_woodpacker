/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:05:34 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/13 12:22:33 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char *ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, count * sizeof(size));
	return ((void*)ptr);
}
