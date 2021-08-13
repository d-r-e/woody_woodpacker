/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:16:04 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/11 12:23:49 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		cpy_end;

	i = 0;
	cpy_end = 0;
	while (i < n)
	{
		if (s2[i] && !cpy_end)
			s1[i] = s2[i];
		else
		{
			s1[i] = '\0';
			cpy_end = 1;
		}
		i++;
	}
	return (s1);
}
