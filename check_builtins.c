/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:31:13 by atolojan          #+#    #+#             */
/*   Updated: 2024/10/08 15:16:10 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char *str, t_list *envp)
{
	char	**splitted;

	splitted = split_ignore_quote((const char *)str, 32);
	if (!ft_memcmp(splitted[0], "echo", 5) || !ft_memcmp(splitted[0], "exit", 5)
			|| !ft_memcmp(splitted[0], "cd", 3) || !ft_memcmp(splitted[0], "pwd", 4)
			|| !ft_memcmp(splitted[0], "env", 4) || !ft_memcmp(splitted[0], "export", 7))
	{
		ft_builtin_cmd((const char **)splitted, envp);
		return (0);
	}
	return (-1);
}
