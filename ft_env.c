/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:00:53 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/20 08:20:31 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_var_name(t_assign *assign, char *str, int start, int len)
{
	char	*s;

	s = get_var_name(assign, str, start, len);
	if (!s)
		return (0);
	assign->var_name = ft_strdup((const char *)s);
	free(s);
	if (!assign->var_name)
		return (0);
	return (1);
}

static int	assign_value(t_assign *assign, char *str, int start, int len)
{
	char	*s;

	if (len > 0)
	{
		s = get_var_name(assign, str, start, len);
		if (!s)
			return (0);
		assign->value = ft_strdup((const char *)s);
		free(s);
		if (!assign->value)
			return (0);
		return (1);
	}
	assign->value = ft_strdup("\0");
	if (!assign->value)
		return (0);
	return (1);
}

static int	handle_equal_case(t_assign *ass, char *str, int pos)
{
	int	val;

	val = 0;
	if (!assign_var_name(ass, str, 0, pos))
		return (0);
	if (str[pos + 1] != '\0')
		val = assign_value(ass, str, pos + 1, ft_strlen(str) - (pos + 1));
	else
		val = assign_value(ass, str, 0, 0);
	return (val);
}

t_assign	*extract_assign(char *str)
{
	t_assign	*assign;
	int			i;

	assign = (t_assign *)malloc(sizeof(t_assign));
	if (!assign)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			if (!handle_equal_case(assign, str, i))
			{
				free(assign);
				return (NULL);
			}
			return (assign);
		}
		i++;
	}
	assign->var_name = ft_strdup((const char *)str);
	if (!assign->var_name)
	{
		free(assign);
		return (NULL);
	}
	assign->value = NULL;
	return (assign);
}

int	ft_env(t_list *envp, int sorted)
{
	t_list		*tmp;
	t_assign	*ass;

	tmp = envp;
	ass = NULL;
	if (sorted == 0)
	{
		while (tmp != NULL)
		{
			ass = extract_assign((char *)tmp->content);
			if (!ass)
				return (1);
			printf("%s=%s\n", ass->var_name, ass->value);
			remove_assign(ass);
			tmp = tmp->next;
		}
	}
	else
	{
		if (export_print(envp, ass, tmp) == 1)
			return (1);
	}
	return (0);
}
