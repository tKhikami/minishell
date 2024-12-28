/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:43:03 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/28 13:39:42 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_atol(char *str, int *err)
{
	long long	ret;
	int			i;
	int			j;
	int			pn;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	pn = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pn = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || \
		((pn == -1 && (ret - 1) > 9223372036854775807) || \
		(pn == 1 && (ret > 9223372036854775807))))
		*err = 1;
	return ((int)((ret * pn) % 256));
}

int	ft_exit(const char **tab)
{
	int	ret;
	int	err;
	int	atol;

	ret = 0;
	err = 0;
	atol = 0;
	if (tab[1] != NULL)
	{
		atol = ft_atol((char *)tab[1], &err);
		if (err)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd((char *)(tab[1]), 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		if (tab[2] != NULL)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
	}
	exit(atol);
}
