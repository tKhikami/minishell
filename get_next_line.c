/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrandri <nyrandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:27:18 by nyrandri          #+#    #+#             */
/*   Updated: 2024/12/16 14:27:22 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/** creat new info **/
char	*ft_new_fd(int fd)
{
	char	*str;
	size_t	size;
	int		val;

	if (fd == -1)
		return (NULL);
	size = sizeof(int);
	str = ft_alloc((4 * size) + BUFFER_SIZE, 1);
	if (str == NULL)
		return (NULL);
	val = 1;
	ft_memcpy(&str[0], &val, size);
	ft_memcpy(&str[size], &fd, size);
	val = 0;
	ft_memcpy(&str[(size * 2)], &val, size);
	ft_memcpy(&str[(size * 3)], &val, size);
	return (str);
}

char	*ft_get_line(char **stock, t_data data, int s_len)
{
	char	*str;
	int		buf_len;

	str = ft_alloc(1, 1);
	if (str == NULL)
		return (free(str), free(*stock), *stock = NULL, NULL);
	while (s_len == 0 || (s_len != buf_len + s_len && str[s_len - 1] != '\n'))
	{
		if (*data.byteread <= *data.cursor)
		{
			*(data.byteread) = read(*(data.fld), data.buffer, BUFFER_SIZE);
			*(data.cursor) = 0;
			if (*data.byteread <= 0 && s_len == 0)
				return (free(str), free(*stock), *stock = NULL, NULL);
		}
		buf_len = *(data.byteread) - *(data.cursor);
		buf_len = ft_poschr(&data.buffer[*(data.cursor)], buf_len);
		str = ft_subtab(str, data.buffer + *(data.cursor), s_len, buf_len);
		*(data.cursor) += buf_len;
		s_len += buf_len;
	}
	if (s_len == 0 && buf_len == 0)
		return (free(str), free(*stock), *stock = NULL, NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	t_data		data;

	if (stock == NULL)
	{
		stock = ft_new_fd(fd);
		if (stock == NULL)
			return (NULL);
	}
	data.nb = (int *)(&stock[0]);
	data.fld = (int *)(&stock[sizeof(int)]);
	data.cursor = (int *)(&stock[sizeof(int) * 2]);
	data.byteread = (int *)(&stock[sizeof(int) * 3]);
	data.buffer = &stock[sizeof(int) * 4];
	return (ft_get_line(&stock, data, 0));
}
