/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:55:38 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/24 16:38:13 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **tab)
{
	int	i;

	i = 1;
	if (tab[1] != NULL)
	{
		if (ft_memcmp(tab[1], "-n", 3) == 0)
		{
			ft_print_tab(&tab[2]);
		}
		else
		{
			ft_print_tab(&tab[1]);
			write(1, "\n", 1);
		}
	}
	else
		write(1, "\n", 1);
	return (0);
}
