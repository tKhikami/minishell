/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:35:25 by atolojan          #+#    #+#             */
/*   Updated: 2024/04/15 12:04:57 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int	read_next(int fd, char *str)
{
	int	byte_read;

	byte_read = read(fd, str, BUFFER_SIZE);
	str[byte_read] = '\0';
	return (byte_read);
}

char	*join_shrink(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0' && s2[j] != '\n')
		str[i++] = s2[j++];
	if (s2 && s2[j] == '\n')
		str[i++] = '\n';
	if (s1)
		free(s1);
	str[i] = '\0';
	return (str);
}

int	get_back_words(char *str)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (str[i] != '\0')
	{
		if (n == 1)
		{
			str[j] = str[i];
			j++;
		}
		if (str[i] == '\n')
			n = 1;
		str[i] = '\0';
		i++;
	}
	return (n);
}
