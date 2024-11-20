/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_substr.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: atolojan <atolojan@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/08/01 09:05:22 by atolojan		   #+#	  #+#			  */
/*	 Updated: 2024/11/11 07:23:58 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	length;
	int		i;
	int		minlen;
	char	*ret;

	i = 0;
	length = ft_strlen(s);
	if (s == NULL || start > length || len < 0 || start < 0)
		return (NULL);
	minlen = min(ft_strlen(&s[start]), len);
	ret = malloc(minlen + 1);
	if (ret != NULL)
	{
		while (i < minlen)
		{
			ret[i] = s[start + i];
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}
