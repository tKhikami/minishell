/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_strtok.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:56:15 by atolojan          #+#    #+#             */
/*   Updated: 2024/09/23 17:29:41 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_reverse_strtok(char *str, char *delims, int (*ignore)(char *, char *))
{
	static int	len;
	static char	*s;

	if (str != NULL)
	{
		s = str;
		len = ft_strlen(str);
	}
	while (len > 0)
	{
		if (ft_strchr(delims, s[len - 1]) != NULL && ignore(s, &s[len - 1]) == 0)
		{
			len--;
			s[len] = '\0';
			return (&s[len + 1]);
		}
		len--;
	}
	if (len == 0)
	{
		len--;
		return (s);
	}
	return (NULL);
}
