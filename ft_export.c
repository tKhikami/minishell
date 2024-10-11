/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:45:47 by atolojan          #+#    #+#             */
/*   Updated: 2024/10/11 15:15:58 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_assign	*char_to_assign(char *str)
{
	t_assign	*assign;
	char		**s;

	assign = (t_assign *) malloc(sizeof (t_assign));
	if (!assign)
		return (NULL);
	s = ft_split(str, '=');
	if (!s)
		return (NULL);
	assign->var_name = ft_strdup(s[0]);
	if (!assign->var_name)
	{
		free(assign);
		free(s);
		return (NULL);
	}
	assign->value = ft_strdup(s[1]);
	if (!assign->value)
	{
		free(assign);
		free(s);
		return (NULL);
	}
	free(s);
	return (assign);
}

t_list	*env_to_tlist(char *env[])
{
	int			i;
	t_list		*envp;
	t_assign	*var;
	char		*content;

	i = 0;
	envp = NULL;
	content = NULL;
	while (env[i] != NULL)
	{
		var = char_to_assign(env[i]);
		if (!var)
		{
			ft_lstclear(&envp, free);
			return (NULL);
		}
		ft_lstadd_back(&envp, ft_lstnew(var));
		i++;
	}
	return (envp);
}

int	is_an_assignment(char *str)
{
	int	i;
	int	nbr_equal;

	i = 1;
	nbr_equal = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			if (str[i - 1] != 32)
			{
				if (str[i + 1] && str[i + 1] != 32)
					nbr_equal++;
				else
					return (0);
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(char *str, char *env[])
{
	t_list	*envp;
	t_list	*export;
	char	**str_splitted;

	envp = env_to_tlist(env);
	if (!envp)
		return (0);
	str_splitted = ft_split(str, 32);
	if (!str_splitted)
	{
		ft_lstclear(&envp, free);
		return (0);
	}
	i = 0;
	while (str_splitted[i] != '\0')
	{
		if (!ft_strncmp((const char *)str_splitted[i], "export", 7))
			handle_export(envp, export, str_splitted, i);
	}
}
