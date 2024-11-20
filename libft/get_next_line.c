/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:33:27 by atolojan          #+#    #+#             */
/*   Updated: 2024/04/17 10:22:04 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	str[BUFFER_SIZE];
	char		*line;
	int			byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof (char) * 1);
	line[0] = '\0';
	line = join_shrink(line, str);
	if (get_back_words(str) > 0)
		return (line);
	byte_read = read(fd, str, BUFFER_SIZE);
	if (byte_read < 0)
		return (free(line), NULL);
	str[byte_read] = '\0';
	while (byte_read > 0)
	{
		line = join_shrink(line, str);
		if (get_back_words(str) == 1)
			break ;
		byte_read = read_next(fd, str);
	}
	if (byte_read == 0 && line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
