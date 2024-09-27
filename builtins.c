/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:08:30 by atolojan          #+#    #+#             */
/*   Updated: 2024/09/27 17:07:56 by atolojan         ###   ########.fr       */
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

t_list	*env_to_tlist(char *env[])
{
	int	i;
	t_list	*envp;
	char	*content;

	i = 0;
	envp = NULL;
	content = NULL;
	while (env[i] != NULL)
	{
		content = ft_strdup(env[i]);
		if (!content)
		{
			ft_lstclear(&envp, free);
			return (NULL);
		}
		ft_lstadd_back(&envp, ft_lstnew(content));
		i++;
	}
	return (envp);
}

int	ft_env(char *env[])
{
	ft_lstiter(envp, print_content);
	ft_lstclear(&envp, free);
	return (0);
}

int	is_an_assignation(char *str)
{
	int	i;
	int	nbr_equal;

	i = 1;
	nbr_equal = 0;
	if (!ft_isalpha(str[0]) || str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			if (i != 0 && str[i - 1] != 32)
			{
				if (str[i + 1] && str[i + 1] != 32)
					nbr_equal++;
			}
		}
		i++;
	}
	if (nbr_equal != 1)
		return (0);
	return (1);
}

int	ft_export(char *str, t_list *envp)
{
	int	assign;

	assign = is_an_assignation(str);
	if (!assign)
		return (0);
	ft_lstadd_back(&envp, ft_lstnew(str));
	return (1);
}
