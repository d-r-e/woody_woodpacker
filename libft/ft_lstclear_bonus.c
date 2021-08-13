/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:22:15 by darodrig          #+#    #+#             */
/*   Updated: 2019/11/14 12:12:00 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!lst || !*lst || !del)
		return ;
	tmp = *lst;
	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp->next;
		(*del)((void *)tmp->content);
		free(tmp);
		tmp = tmp2;
	}
	*lst = NULL;
}
