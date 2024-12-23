/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrandri <nyrandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:09:20 by nyrandri          #+#    #+#             */
/*   Updated: 2024/12/22 16:09:22 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strtok(char *str, char *delims, \
		int (*ignore)(char *, char *))
{
	static char	*s;
	char		*tmp;

	if (str != NULL)
		s = str;
	tmp = s;
	while (s != NULL)
	{
		s = ft_substrchr(s, delims);
		if (s != NULL && ignore(tmp, s) == 0)
		{
			ft_bzero(s, ft_strlen(delims));
			s = s + ft_strlen(delims);
			return (s);
		}
	}
	return (NULL);
}
