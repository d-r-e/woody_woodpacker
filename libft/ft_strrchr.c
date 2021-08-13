/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:47:53 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/14 15:18:53 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = ft_strlen(s);
	ptr = (char*)s + i;
	if (c == '\0')
		return (ptr);
	while (i >= 0)
	{
		if (*ptr == c)
			return (ptr);
		ptr--;
		i--;
	}
	return (NULL);
}
