/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:43:03 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/17 10:44:02 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(const char **tab)
{
	int	ret;

	ret = 0;
	if (tab[1] != NULL)
	{
		if (ft_isnumber(tab[1]) == -1)
		{
			printf("\"%s\" is not a numeric argument\n", tab[1]);
			exit(2);
		}
		else
			exit(ft_atoi(tab[1]) % 256);
	}
	exit(0);
}
