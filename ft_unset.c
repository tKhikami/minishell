/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:11:25 by atolojan          #+#    #+#             */
/*   Updated: 2024/10/17 17:27:01 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_assign(void *content)
{
	t_assign	*assign;

	assign = (t_assign *)content;
	free(assign->var_name);
	free(assign->value);
	free(assign);
}

int	ft_unset(t_list *env, char *str)
{
	t_list	*tmp;
	t_assign	*assign;

	tmp = env;
	assign = (t_assign *)(tmp->content);
	while (ft_memcmp(assign->var_name, str, ft_strlen(str)) && tmp)
		tmp = tmp->next;
	if (!tmp)
		return (1);
	ft_lstdelone(tmp, remove_assign);
	tmp = NULL;
	return (0);
}
