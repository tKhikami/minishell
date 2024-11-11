/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:45:47 by atolojan          #+#    #+#             */
/*   Updated: 2024/11/11 16:50:15 by nyrandri         ###   ########.fr       */
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

t_assign	*extract_assign(char *str)
{
	t_assign	*assign;
	char		*s;
	int		i;
	int			equal;

	equal = 0;
	assign = (t_assign *) malloc(sizeof (t_assign));
	if (!assign)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			s = get_var_name(assign, str, 0, i);
			if (!s)
				return (NULL);
			assign->var_name = ft_strdup((const char *)s);
			if (!assign->var_name)
			{
				free(assign);
				return (NULL);
			}
			free(s);
			if (str[i + 1] != '\0')
			{
				s = get_var_name(assign, str, i + 1, ft_strlen(str) - (i + 1));
				if (!s)
				{
					free(assign->var_name);
					return (NULL);
				}
				assign->value = ft_strdup((const char *)s);
				if (!assign->value)
				{
					free(s);
					free(assign->var_name);
					free(assign);
					return (NULL);
				}
			}
			else
			{
				assign->value = ft_strdup("\0");
				if (!assign->value)
				{
					free(assign->var_name);
					free(assign);
					return (NULL);
				}
			}
			equal = 1;
			break ;
		}
		i++;
	}
	if (equal == 0)
	{
		assign->var_name = ft_strdup((const char *)str);
		if (!assign->var_name)
		{
			free(assign);
			return (NULL);
		}
		assign->value = NULL;
	}
	return (assign);
}

void	env_to_tlist(t_list **envp, char *env[], int count)
{
	int			i;

	i = 0;
	while (env[i] != NULL && i != count)
	{
		if (is_an_assignment(env[i]))
		{
			ft_lstadd_back(envp, ft_lstnew(ft_strdup(env[i])));
		}
		i++;
	}
}

int	is_an_assignment(char *str)
{
	int	i;
	int	after_equal;

	i = 1;
	after_equal = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == 32 || str[i + 1] == 32)
				return (0);
			after_equal = 1;
		}
		//else if (!ft_isalnum(str[i]) && str[i] != '_' && !after_equal)
		//	return (0);
		i++;
	}
	return (1);
}

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

void	handle_export(t_list **exp, char **s, int i)
{
	int			a;
	char		*to_find;
	t_assign	*ass;

	a = 1;
	while (s[i + a] != NULL)
	{
		to_find = search_value(*exp, s[i + a]);
		if (to_find)
		{
			ass = extract_assign(s[i + a]);
			if (ass->value != NULL)
			{
				ft_unset(exp, ass->var_name);
				env_to_tlist(exp, &s[i + a], 1);
			}
			else
			{
				remove_assign(ass);
				return ;
			}
			remove_assign(ass);
		}
		else
		{
			env_to_tlist(exp, &s[i + a], 1);
			return ;
		}
		a++;
	}
	if (a == 1)
		ft_env(*exp, 1);
}

int	ft_export(t_list **exp, char *str)
{
	char			**str_splitted;

	str_splitted = ft_split(str, 32);
	if (!str_splitted)
		return (1);
	handle_export(exp, str_splitted, 0);
	return (0);
}
