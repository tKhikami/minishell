/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:08:30 by atolojan          #+#    #+#             */
/*   Updated: 2024/11/07 16:44:40 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(const char *path)
{
	if (chdir(path) != 0)
	{
		perror((char *) path);
		return (1);
	}
	return (0);
}

int	ft_pwd(char *tab)
{
	char	path[100];

	if (tab != NULL)
	{
		write(2, "pwd: too many arguments\n", 24);
		return (0);
	}
	return (ft_printf("%s\n", getcwd(path, 100)));
}

void	print_content(void *content)
{
	printf("%s\n", (char *) content);
}

void	sort_list(t_list **sorted)
{
	t_list	*i;
	t_list	*j;
	t_list	*min_idx;
	char	*tmp;

	if (*sorted == NULL || (*sorted)->next == NULL)
		return ;
	i = *sorted;
	while (i->next != NULL)
	{
		min_idx = i;
		j = i->next;
		while (j)
		{
			if (ft_strcmp(j->content, min_idx->content) < 0)
				min_idx = j;
			j = j->next;
		}
		if (min_idx != i)
		{
			tmp = min_idx->content;
			min_idx->content = i->content;
			i->content = tmp;
		}
		i = i->next;
	}
}
		
t_list	*make_sort_list(t_list **envp)
{
	t_list	*sorted;
	t_list	*tmp;
	char	*str;

	sorted = NULL;
	tmp = *envp;
	while (tmp)
	{
		str = ft_strdup(tmp->content);
		if (!str)
		{
			ft_lstclear(&sorted, free);
			return (NULL);
		}
		ft_lstadd_back(&sorted, ft_lstnew(str));
		tmp = tmp->next;
	}
	sort_list(&sorted);
	return (sorted);
}

int	ft_env(t_list *envp, int sorted)
{
	t_list		*tmp;
	t_list		*sort;
	t_assign	*ass;

	tmp = envp;
	if (sorted == 0)
	{
		while (tmp != NULL)
		{
			ass = extract_assign((char *)tmp->content);
			printf("%s=%s\n", ass->var_name, ass->value);
			remove_assign(ass);
			tmp = tmp->next;
		}
	}
	else
	{
		sort = make_sort_list(&envp);
		tmp = sort;
		while (tmp != NULL)
		{
			ass = extract_assign((char *)tmp->content);
			if (ass->value == NULL)
				printf("declare -x %s\n", ass->var_name);
			else if ((ass->value)[0] == '"')
				printf("declare -x %s=%s\n", ass->var_name, ass->value);
			else
				printf("declare -x %s=\"%s\"\n", ass->var_name, ass->value);
			remove_assign(ass);
			tmp = tmp->next;
		}
		ft_lstclear(&sort, free);
	}
	return (0);
}
