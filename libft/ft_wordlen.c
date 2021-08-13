/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 14:32:34 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/11 15:45:00 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns the length of a word in a string, until the first ocurrence of c.
*/

#include "libft.h"

int	ft_wordlen(char *s, char c)
{
	int count;

	count = 0;
	while (*s != '\0' && *s != c)
	{
		count++;
		s++;
	}
	return (count);
}
