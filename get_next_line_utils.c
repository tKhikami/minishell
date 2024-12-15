/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrandri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:32:02 by nyrandri          #+#    #+#             */
/*   Updated: 2024/04/15 13:38:53 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_alloc(size_t nmemb, size_t size)
{
	char	*mem;
	size_t	i;

	i = 0;
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		mem[i] = 0;
		i++;
	}
	return ((void *)mem);
}

/** substr modif**/
char	*ft_subtab(char *str, char *buffer, int str_len, int buf_len)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(str_len + buf_len + 1);
	if (result == NULL)
		return (NULL);
	while (i < str_len)
	{
		result[i] = str[i];
		i++;
	}
	i = 0;
	while (i < buf_len)
	{
		result[i + str_len] = buffer[i];
		i++;
	}
	result[str_len + buf_len] = '\0';
	free(str);
	return (result);
}

/** return len of concat part start in cursor **/
int	ft_poschr(const char *s, int len)
{
	int	i;

	i = 0;
	if (len < 0)
		return (0);
	while (i < len)
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*p_dest;
	const char	*p_src;

	p_dest = dest;
	p_src = src;
	i = 0;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}
