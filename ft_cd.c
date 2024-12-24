/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:56:31 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/20 08:11:48 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(const char *path)
{
	if (path == NULL)
	{
		write(2, "please provide a relative or absolute path\n", 44);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror((char *) path);
		return (1);
	}
	return (0);
}
