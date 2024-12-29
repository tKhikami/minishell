/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrandri <nyrandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:06:33 by nyrandri          #+#    #+#             */
/*   Updated: 2024/12/29 14:57:42 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	del_variable(void *var)
{
	t_assign	*tmp;

	tmp = (t_assign *)var;
	if (var != NULL)
	{
		free(tmp->var_name);
		free(tmp->value);
		free(tmp);
	}
}

int	print_variable(void *var)
{
	t_assign	*tmp;
	int			ret;

	tmp = (t_assign *)var;
	ret = 0;
	if (tmp == NULL)
		ret += printf("NULL");
	else
		ret += printf("%s || %s", tmp->var_name, tmp->value);
	ret += printf("\n");
	return (ret);
}

t_list	*get_one_variable(char *str)
{
	t_assign	*tmp;
	t_list		*lst;
	char		*ptr;

	ptr = ft_strchr(str, '=');
	tmp = malloc(sizeof(t_assign));
	if (tmp != NULL)
	{
		tmp->var_name = ft_substr(str, 0, ptr - str);
		tmp->value = ft_strdup(ptr + 1);
		if (tmp->var_name == NULL || tmp->value == NULL)
		{
			free(tmp->var_name);
			free(tmp->value);
			free(tmp);
			return (NULL);
		}
	}
	lst = ft_lstnew(tmp);
	if (lst == NULL)
		free(tmp);
	return (lst);
}

t_list	*get_all_variable(char **tab)
{
	int		i;
	t_list	*lst;
	t_list	*tmp;

	if (tab == NULL)
		return (NULL);
	i = ft_tablen(tab) - 1;
	lst = NULL;
	while (i >= 0)
	{
		tmp = get_one_variable(tab[i]);
		if (tmp == NULL)
		{
			ft_lstclear(&lst, &del_variable);
			return (NULL);
		}
		ft_lstadd_front(&lst, tmp);
		i--;
	}
	return (lst);
}

t_list	*variable_chr(t_list *env, char *str)
{
	t_list	*tmp;
	t_assign	*ass;

	if (str == NULL)
	{
		return (NULL);
	}
	tmp = env;
	while (tmp != NULL)
	{
		ass = extract_assign((char *)(tmp->content));
		if (!ass)
			return (NULL);
		if (ft_strcmp(ass->var_name, str) == 0)
		{
			remove_assign(ass);
			return (tmp);
		}
		remove_assign(ass);
		tmp = tmp->next;
	}
	return (tmp);
}

char	*variable_chr_tab(char *variable, char **envp)
{
	int	i;
	int	tab_len;
	int	min;

	i = 0;
	tab_len = ft_tablen(envp);
	while (i < tab_len)
	{
		min = ft_min(ft_strlen(variable), ft_strlen(envp[i]));
		if (ft_memcmp(envp[i], variable, min) == 0 && envp[i][min] == '=')
			break ;
		i++;
	}
	if (i == tab_len)
		return (NULL);
	return (ft_strdup(&envp[i][min + 1]));
}
