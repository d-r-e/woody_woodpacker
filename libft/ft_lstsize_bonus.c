/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:25:12 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/14 11:58:24 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*ref;

	if (!lst)
		return (0);
	ref = lst;
	i = 0;
	while (ref != NULL)
	{
		ref = ref->next;
		i++;
	}
	return (i);
}
