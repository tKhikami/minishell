/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:45:47 by atolojan          #+#    #+#             */
/*   Updated: 2024/10/17 14:08:17 by atolojan         ###   ########.fr       */
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
	t_assign	*var;

	i = 0;
	var = NULL;
	while (env[i] != NULL && i != count)
	{
		if (is_an_assignment(env[i]))
		{
			var = extract_assign(env[i]);
			if (!var)
			{
				ft_lstclear(envp, free);
				return ;
			}
			ft_lstadd_back(envp, ft_lstnew(var));
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

void	handle_export(t_list **exp, char **s, int i, int history)
{
	int	a;

	a = 1;
	if (exp && i != 0 && !history)
		ft_lstclear(exp, free);
	while (s[i + a] != NULL)
	{
		if (is_an_assignment(s[i + a]))
		{
			printf("si : %s\n", s[i + a]);
			env_to_tlist(exp, &s[i + a], 1);
		}
		else
			break ;
		a++;
	}
}

int	ft_export(t_list **exp, char *str)
{
	static t_list	*tmp;
	char			**str_splitted;
	int				i;
	static int		history;

	str_splitted = ft_split(str, 32);
	if (!str_splitted)
		return (1);
	i = 0;
	while (str_splitted[i] != NULL)
	{
		if (!ft_strncmp((const char *)str_splitted[i], "export", 7))
		{
			handle_export(exp, str_splitted, i, history);
			history = 1;
			return (0);
		}
		else if (is_an_assignment(str_splitted[i]))
		{
			env_to_tlist(&tmp, &str_splitted[i], 1);
			printf("ajouter\n");
		}
		i++;
	}
	return (1);
}
