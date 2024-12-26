/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_builtin_cmd.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/16 13:28:57 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/16 13:28:57 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_memcmp(cmd, "echo", 5) \
			|| !ft_memcmp(cmd, "exit", 5) \
			|| !ft_memcmp(cmd, "cd", 3) \
			|| !ft_memcmp(cmd, "pwd", 4) \
			|| !ft_memcmp(cmd, "env", 4) \
			|| !ft_memcmp(cmd, "unset", 6) \
			|| !ft_memcmp(cmd, "export", 7))
	{
		return (1);
	}
	return (0);
}

int execve_builtin(char **tab, t_list *env)
{
	if (tab != NULL)
	{
		if (ft_memcmp(tab[0], "echo", 5) == 0)
			return (ft_echo(tab));
		else if (ft_memcmp(tab[0], "exit", 5) == 0)
			return (ft_exit((const char **)tab));
		else if (ft_memcmp(tab[0], "cd", 3) == 0)
			return (ft_cd((const char *) tab[1]));
		else if (ft_memcmp(tab[0], "pwd", 4) == 0)
			return (ft_pwd((char *)tab[1]));
		else if (ft_memcmp(tab[0], "export", 7) == 0)
			return (ft_export(&env, &tab[0]));
		else if (ft_memcmp(tab[0], "env", 4) == 0)
			return (ft_env(env, 0));
		else if (ft_memcmp(tab[0], "unset", 6) == 0)
			return (ft_unset(&env, tab[1]));
	}
	return (1);
}
