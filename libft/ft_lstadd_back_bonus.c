/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:31:01 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/01 08:31:03 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_element)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new_element;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new_element;
	}
}
