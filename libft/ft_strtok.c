/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:56:15 by atolojan          #+#    #+#             */
/*   Updated: 2024/09/16 11:00:39 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtok(char *str, const char *delims)
{
	static char	*s;
	static int	token;
	int			tmp;
	int			i;
	int			j;

	i = token;
	tmp = i;
	if (str != NULL)
		ft_strlcpy(s, str, ft_strlen(str));
	while (s[i] != '\0')
	{
		j = -1;
		while (delims[++j] != '\0')
		{
			if (s[i] == delims[j])
			{
				token = i + 1;
				s[i] = '\0';
				return (s[tmp]);
			}
		}
		i++;
	}
	return (NULL);
}
