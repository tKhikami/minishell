/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:05:11 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/02 16:22:48 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = (int)ft_strlen((char *)s1) - 1;
	while (s1[i] != '\0' && is_in(s1[i], set))
		i++;
	while (j >= 0 && is_in(s1[j], set))
		j--;
	if (j == -1)
		return (ft_strdup(""));
	str = malloc((j - i + 1) + 1);
	if (!str)
		return (NULL);
	k = 0;
	while (i <= j && s1[i] != '\0')
	{
		str[k] = s1[i];
		i++;
		k++;
	}
	str[k] = '\0';
	return (str);
}
