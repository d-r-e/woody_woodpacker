/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:32:31 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/14 16:35:52 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (len == 0 || start > ft_strlen(s))
	{
		if (!(sub = malloc(sizeof(char))))
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	if (!(sub = malloc(len * sizeof(char) + (1 * sizeof(char)))))
		return (NULL);
	s += start;
	i = 0;
	while (i < len && s[i] != '\0')
	{
		sub[i] = s[i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
