/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:08:30 by atolojan          #+#    #+#             */
/*   Updated: 2024/09/26 10:07:50 by atolojan         ###   ########.fr       */
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

int	ft_export(char *env[])
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
			return (-1);
		}
		ft_lstadd_back(&envp, ft_lstnew(content));
		i++;
	}
	ft_lstiter(envp, print_content);
	ft_lstclear(&envp, free);
	return (0);
}
