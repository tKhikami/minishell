/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:05:22 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/01 09:05:24 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t				i;
	size_t				j;
	char				*str;
	unsigned int		l;

	l = ft_strlen(s);
	if (!s)
		len = 0;
	if (start > l)
		len = 0;
	else if (len > l - start)
		len = l - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = start;
	while (i < len && start < l && s[j] != '\0')
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
