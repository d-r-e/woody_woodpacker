/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:32:12 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/08 15:34:44 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	buff;

	i = 0;
	len = ft_strlen(str);
	while (len - 1 > i)
	{
		buff = str[i];
		str[i] = str[len - 1];
		str[len - 1] = buff;
		len--;
		i++;
	}
	return (str);
}
