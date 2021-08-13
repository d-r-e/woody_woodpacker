/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:34:24 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/13 12:20:38 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**splitter(char const *s, char c)
{
	int		i;
	int		j;
	char	**t;

	i = 0;
	if (!(t = (char**)malloc(sizeof(char*) * (ft_wordcount((char*)s, c) + 1))))
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		j = 0;
		if (!(t[i] = (char*)malloc((ft_wordlen((char*)s, c) + 1))))
			return (NULL);
		while (*s != c && *s != '\0')
		{
			t[i][j] = *s;
			j++;
			s++;
		}
		t[i][j] = '\0';
		i++;
	}
	t[i] = NULL;
	return (t);
}

char		**ft_split(char const *s, char c)
{
	char	*trimmed;
	char	totrim[2];
	char	**t;

	if (!s)
		return (NULL);
	if (ft_strcmp(s, "") == 0)
	{
		if (!(t = malloc(sizeof(char*))))
			return (NULL);
		*t = NULL;
		return (t);
	}
	totrim[0] = c;
	totrim[1] = '\0';
	if (!(trimmed = ft_strtrim(s, totrim)))
		return (NULL);
	if (!(t = splitter(trimmed, c)))
		return (NULL);
	free(trimmed);
	return (t);
}
