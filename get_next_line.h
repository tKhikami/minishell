/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrandri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:02 by nyrandri          #+#    #+#             */
/*   Updated: 2024/04/15 13:38:19 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_data
{
	int		*nb;
	int		*fld;
	int		*cursor;
	int		*byteread;
	char	*buffer;
}				t_data;

char	*get_next_line(int fd);
void	*ft_alloc(size_t nmemb, size_t size);
char	*ft_subtab(char *str, char *buffer, int str_len, int buf_len);
int		ft_poschr(const char *s, int len);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
