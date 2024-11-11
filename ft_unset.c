/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:11:25 by atolojan          #+#    #+#             */
/*   Updated: 2024/11/07 16:44:50 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_assign(t_assign *assign)
{
	free(assign->var_name);
	free(assign->value);
	free(assign);
}

int	ft_unset(t_list **env, char *str)
{
	t_list		*tmp;
	t_list		*previous;
	t_assign	*assign;

	tmp = *env;
	previous = NULL;
	while (tmp)
	{
		assign = extract_assign((char *)tmp->content);
		if (ft_memcmp(assign->var_name, str, ft_strlen(str)) == 0)
		{
			if (previous == NULL)
				*env = tmp->next;
			else
				previous->next = tmp->next;
			remove_assign(assign);
            free(tmp);
			return (0);
		}
		remove_assign(assign);
		previous = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	return (0);
}
