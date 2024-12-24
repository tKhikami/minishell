/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:45:47 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/19 16:25:56 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_value(t_list *exp, char *str)
{
	t_assign	*assign;
	t_list		*tmp;
	char		*to_find;

	tmp = exp;
	while (tmp)
	{
		assign = extract_assign((char *)tmp->content);
		if (!ft_memcmp(assign->var_name, str, ft_strlen(assign->var_name)))
		{
			to_find = ft_strdup(assign->var_name);
			remove_assign(assign);
			return (to_find);
		}
		remove_assign(assign);
		tmp = tmp->next;
	}
	tmp = NULL;
	return (NULL);
}

int	existing_value(t_list **exp, char **s, int i, int a)
{
	t_assign	*ass;

	ass = extract_assign(s[i + a]);
	if (ass->value != NULL)
	{
		ft_unset(exp, ass->var_name);
		env_to_tlist(exp, &s[i + a], 1);
	}
	else
	{
		remove_assign(ass);
		return (1);
	}
	remove_assign(ass);
	return (0);
}

int	handle_export(t_list **exp, char **s, int i)
{
	int		a;
	char	*to_find;

	a = 1;
	while (s[i + a] != NULL)
	{
		to_find = search_value(*exp, s[i + a]);
		if (to_find)
		{
			if (existing_value(exp, s, i, a) == 1)
				return (0);
		}
		else
		{
			return (env_to_tlist(exp, &s[i + a], 1));
		}
		a++;
	}
	if (a == 1)
		ft_env(*exp, 1);
	return (0);
}

void	sort_list(t_list **sorted)
{
	t_list	*i[3];
	char	*tmp;

	if (*sorted == NULL || (*sorted)->next == NULL)
		return ;
	i[0] = *sorted;
	while (i[0]->next != NULL)
	{
		i[2] = i[0];
		i[1] = i[0]->next;
		while (i[1])
		{
			if (ft_strcmp(i[1]->content, i[2]->content) < 0)
				i[2] = i[1];
			i[1] = i[1]->next;
		}
		if (i[2] != i[0])
		{
			tmp = i[2]->content;
			i[2]->content = i[0]->content;
			i[0]->content = tmp;
		}
		i[0] = i[0]->next;
	}
}

int	ft_export(t_list **exp, char *str)
{
	char	**str_splitted;

	str_splitted = ft_split(str, 32);
	if (!str_splitted)
		return (1);
	handle_export(exp, str_splitted, 0);
	return (0);
}
