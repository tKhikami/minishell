/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:31:24 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/01 08:31:28 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (*lst == NULL)
		*lst = NULL;
	else
	{
		temp = *lst;
		del((*lst)->content);
		*lst = (*lst)->next;
		free((void *)temp);
		ft_lstclear(lst, del);
	}
}
