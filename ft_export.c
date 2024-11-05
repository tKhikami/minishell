/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:45:47 by atolojan          #+#    #+#             */
/*   Updated: 2024/11/05 16:38:11 by atolojan         ###   ########.fr       */
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
	size_t		i;
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
				if (str[i + 1] == '"')
					i++;
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
		assign->value = ft_strdup("\0");
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
		else if (!ft_isalnum(str[i]) && str[i] != '_' && !after_equal)
			return (0);
		i++;
	}
	return (1);
}

char	*search_value(t_list *exp, char *str)
{
	t_assign	*assign;
	t_list		*tmp;
	//char		*to_find;

	tmp = exp;
	while (tmp)
	{
		assign = extract_assign((char *)tmp->content);
		if (!ft_memcmp(assign->var_name, str, ft_strlen(assign->var_name)))
		{
			//to_find = ft_strdup(assign->var_name);
			free(assign->var_name);
			free(assign->value);
			free(assign);
			return ((char *)tmp->content);
		}
		free(assign->var_name);
		free(assign->value);
		free(assign);
		tmp = tmp->next;
	}
	tmp = NULL;
	return (NULL);
}

int	export_position(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
		i++;
	j = 0;
	while (str[j] && ft_strncmp((const char *)str[j], "export", 7))
		j++;
	if (j != i)
		return (j);
	return (-1);
}

void	handle_export(t_list **exp, char **s, int i, t_list *tmp)
{
	int		a;
	char	*to_find;

	a = 1;
	while (s[i + a] != NULL)
	{
		to_find = search_value(tmp, s[i + a]);
		if (to_find)
		{
			ft_unset(exp, s[i + a]);
			env_to_tlist(exp, &to_find, 1);
		}
		else if (is_an_assignment(s[i + a]))
			env_to_tlist(exp, &s[i + a], 1);
		else
			break ;
		a++;
	}
	if (a == 1)
	{
		ft_env(*exp, 1);
	}
}

int	ft_export(t_list **exp, char *str)
{
	static t_list	*tmp;
	char			**str_splitted;
	int				i;
	int				export_pos;

	str_splitted = ft_split(str, 32);
	if (!str_splitted)
		return (1);
	i = 0;
	export_pos = export_position(str_splitted);
	if (export_pos == -1)
	{
		while (str_splitted[i])
		{
			env_to_tlist(&tmp, &str_splitted[i], 1);
			i++;
		}
		return (0);
	}
	else
	{
		i = export_pos;
		handle_export(exp, str_splitted, i, tmp);
		return (0);
	}
	return (1);
}
