/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:08:30 by atolojan          #+#    #+#             */
/*   Updated: 2024/10/17 12:12:28 by atolojan         ###   ########.fr       */
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

int	ft_env(t_list *envp, t_list *exp)
{
	t_list *tmp;

	tmp = envp;
	while (tmp != NULL)
	{
		t_assign *ass = (t_assign *)(tmp->content);
		printf("key : %s, value : %s\n", ass->var_name, ass->value);
		tmp = tmp->next;
	}
	//(void)exp;
	tmp = exp;
	while (tmp != NULL)
	{
		t_assign *ass = (t_assign *)(tmp->content);
		printf("key : %s, value : %s\n", ass->var_name, ass->value);
		tmp = tmp->next;
	}
	tmp = NULL;
	return (0);
}
