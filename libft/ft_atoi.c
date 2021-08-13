/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:17:38 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/14 14:37:19 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	res;
	unsigned long	limits;
	int				negative;

	negative = 1;
	res = 0;
	limits = (unsigned long)(9223372036854775807 / 10);
	while (*str && ft_isspace(*str))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		if ((res > limits || (res == limits && (*str - '0') > 7))
				&& negative == 1)
			return (-1);
		else if ((res > limits || (res == limits && (*str - '0') > 8))
				&& negative == -1)
			return (0);
		res = res * 10 + (*str - 48);
		++str;
	}
	return ((int)res * negative);
}
