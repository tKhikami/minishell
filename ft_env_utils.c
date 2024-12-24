/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:28:09 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/19 16:36:33 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(t_assign *assign, char *str, int begin, int len)
{
	char	*s;

	s = ft_substr((const char *)str, begin, len);
	if (!s)
	{
		free(assign);
		return (NULL);
	}
	return (s);
}

int	is_an_assignment(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == 32 || str[i + 1] == 32)
				return (0);
		}
		i++;
	}
	return (1);
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

int	env_to_tlist(t_list **envp, char *env[], int count)
{
	int			i;

	i = 0;
	while (env[i] != NULL && i != count)
	{
		if (is_an_assignment(env[i]))
		{
			ft_lstadd_back(envp, ft_lstnew(ft_strdup(env[i])));
		}
		else
		{
			write(2, "minishell: export: `", 9);
			write(2, env[i], ft_strlen(env[i]));
			write(2, "`: not a valid identifier\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export_print(t_list *envp, t_assign *ass, t_list *tmp)
{
	t_list		*sort;
	int			success;

	success = 0;
	sort = make_sort_list(&envp);
	if (!sort)
		return (1);
	tmp = sort;
	while (tmp != NULL && success == 0)
	{
		ass = extract_assign((char *)tmp->content);
		if (!ass)
			success = 1;
		if (ass && ass->value == NULL)
			printf("declare -x %s\n", ass->var_name);
		else if (ass && (ass->value)[0] == '"')
			printf("declare -x %s=%s\n", ass->var_name, ass->value);
		else if (ass)
			printf("declare -x %s=\"%s\"\n", ass->var_name, ass->value);
		if (ass)
			remove_assign(ass);
		tmp = tmp->next;
	}
	ft_lstclear(&sort, free);
	return (success);
}
